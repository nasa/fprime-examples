""" implementation of framing plugin to support a minimal protocol
"""
import struct
import sys
import copy

from fprime.common.models.serialize.numerical_types import U32Type
from fprime_gds.common.communication.framing import FramerDeframer, FpFramerDeframer
from fprime_gds.plugin.definitions import gds_plugin
from fprime_gds.common.communication.checksum import calculate_checksum


@gds_plugin(FramerDeframer)
class DecafFramerDeframer(FramerDeframer):
    """ Implementation of a framing plugin to support a "Decaf" protocol
    """
    START_TOKEN = 0xDECAFBAD
    HEADER_TOKEN_FORMAT = ">I"
    HEADER_SIZE = 8   # 4 bytes for start token + 4 bytes for size
    TRAILER_SIZE = 4  # 4 bytes CRC32 checksum

    MAXIMUM_DATA_SIZE = 4096  # Maximum size of data in a single packet

    def __init__(self):
        self.sequence_number = 0

    def frame(self, data):
        """ Frame the supplied data according to the Decaf protocol. """
        framed = struct.pack(
            ">I", self.START_TOKEN
        )
        framed += struct.pack(
            ">I", len(data)
        )
        framed += data
        framed += struct.pack(">I", calculate_checksum(framed, "crc32"))
        return framed


    def deframe(self, data, no_copy=False):
        """ Attempt to deframe the supplied data stream, returning the first packet found.
        
        This will look for the start and size tokens in the data stream. If any of the following checks fail, the first 
        byte of the stream will be discarded and the process will continue until no data is left or a valid packet is found.

        1. Looks at the beginning of the stream, and discards data until it find a valid start token. 
        2. Read length token, validate data length
        3. Compute CRC of the message and compare it with the transmitted CRC
        4. If all checks pass, return the data and the remaining stream.
        """
        discarded = b""
        if not no_copy:
            data = copy.copy(data)
        # Continue until there is not enough data for the header, or until a packet is found (return)
        while len(data) >= self.HEADER_SIZE:
            # Read header information including start token and size and check if we have enough for the total size
            start, data_size = struct.unpack_from(">II", data)
            total_size = self.HEADER_SIZE + data_size + self.TRAILER_SIZE
            # Invalid frame, rotate away a Byte and keep processing
            if (
                start != self.START_TOKEN
                or data_size >= self.MAXIMUM_DATA_SIZE
            ):
                discarded += data[0:1]
                data = data[1:]
                continue
            # If the pool is large enough to read the whole frame, then read it
            if len(data) >= total_size:
                deframed, transmitted_checksum = struct.unpack_from(
                    f">{data_size}sI", data, FpFramerDeframer.HEADER_SIZE
                )
                # If the checksum is valid, return the packet. Otherwise continue to rotate
                if transmitted_checksum == calculate_checksum(
                    data[: data_size + FpFramerDeframer.HEADER_SIZE],
                    "crc32"
                ):
                    data = data[total_size:]
                    return deframed, data, discarded
                print(
                    "[WARNING] Checksum validation failed.",
                    file=sys.stderr,
                )
                # Bad checksum, rotate 1 and keep looking for non-garbage
                discarded += data[0:1]
                data = data[1:]
                continue
            # Case of not enough data for a full packet, return hoping for more later
            return None, data, discarded
        return None, data, discarded

    @classmethod
    def get_name(cls):
        """ Name of this implementation provided to CLI """
        return "decaf"

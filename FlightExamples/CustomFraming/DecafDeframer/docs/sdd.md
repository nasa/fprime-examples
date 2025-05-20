# Svc::DecafDeframer

The `Svc::DecafDeframer` component receives [Decaf frames](../../README.md) on its input port, takes off the header and trailer (sometimes referred to as "footer"), and passes the encapsulated payload to a downstream component (usually the [`Svc.FprimeRouter`](../../FprimeRouter/docs/sdd.md)).

## Internals

The `Svc::DecafDeframer` component is an implementation of the [DeframerInterface](../../Interfaces/DeframerInterface.fppi) for the F´ communications protocol. It receives an F´ frame (in a [Fw::Buffer](../../../Fw/Buffer/docs/sdd.md) object) on its `dataIn` input port, modifies the input buffer to remove the header and trailer, and sends it out through its `dataOut` output port. 

Ownership of the buffer is transferred to the component connected to the `dataOut` output port. The input buffer is modified by subtracting the header and trailer size from the buffer's length, and offsetting the buffer's data pointer to point to the start of the packet data.

### Frame validation

The passed-in `data` field (of type `Fw::Buffer`) of the `Svc.ComDataWithContext` input port is validated for the following conditions:
- The buffer is large enough to contain the header and trailer
- The buffer starts with the F´ start word
- The buffer length is equal to (or larger than) the packet length field in the frame header
- The CRC field of the frame is equal to the CRC calculated over the frame header and payload

If any of these conditions are not met, the frame is dropped meaning no payload is passed to the output port and the input `Fw::Buffer` is deallocated.

## Requirements

Requirement | Description | Rationale | Verification Method
----------- | ----------- | ----------| -------------------
SVC-DEFRAMER-001 | `Svc::DecafDeframer` shall extract the payload field from input buffers that represent a valid F Prime frame as specified by the [F Prime Protocol](../../FprimeProtocol/docs/sdd.md) | Deframe valid frames and extract payload | Unit test |
SVC-DEFRAMER-002 | `Svc::DecafDeframer` shall return ownership of input buffers that are not a valid F Prime frame as specified by the [F Prime Protocol](../../FprimeProtocol/docs/sdd.md) | Drop invalid frames | Unit test |

## Port Descriptions

| Kind | Name | Type | Description |
|---|---|---|---|
| `guarded input` | `dataIn` | `Svc.ComDataWithContext` | Receives a frame for deframing |
| `output` | `dataOut` | `Svc.ComDataWithContext` | Emits deframed data (F´ packets) |
| `sync input` | `dataReturnIn` | `Svc.ComDataWithContext` | Receives ownership of the emitted data back |
| `output` | `dataReturnOut` | `Svc.ComDataWithContext` | Returns ownership of the input buffer back to the sender |


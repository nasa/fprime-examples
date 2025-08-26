""" Ground derived channels implementation

This script takes in sine.Y values and calculates cosine.Y
"""
import math
from fprime_gds.common.handlers import DataHandlerPlugin
from fprime_gds.plugin.definitions import gds_plugin


@gds_plugin(DataHandlerPlugin)
class CosineDeriver(DataHandlerPlugin):
    """ Plugin to derive cosine as a new telemetry value

    This plugin will derive the cosine from ExamplesDeployment.sine.Y and publish it back as the channel
    "ExamplesDeployment(Ground).cosine.Y".
    """
    def get_handled_descriptors(self):
        """ List descriptors of F Prime data types that this plugin can handle """
        return ["FW_PACKET_TELEM"]
    
    @classmethod
    def get_name(cls):
        """ Return the name of the plugin """
        return "cosine-deriver"
    
    @classmethod
    def get_arguments(cls):
        """ Return argument spec for ZMQ connection string """
        return {}


    def data_callback(self, data, source):
        """ Handle data objects plugged into the GDS
        """
        # Filter down to the exact channel "ExamplesDeployment.sine.Y"
        if "ExamplesDeployment.sine.Y" != data.template.get_full_name():
            return
        cosine_value = math.cos(math.asin(data.get_val_obj().val))
        # Publish the new value under its name, while reusing the time object
        self.publisher.publish_channel("ExamplesDeployment(Ground).cosine.Y", cosine_value, data.time)

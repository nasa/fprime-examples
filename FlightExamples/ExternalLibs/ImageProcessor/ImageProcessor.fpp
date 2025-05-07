module ExternalLibs {

    @ Component for F Prime FSW framework.
    passive component ImageProcessor {

        @ Process images loaded into the internal array
        sync command PROCESS_IMAGES() opcode 1

        @ Read onboard image file into the ImageProcessor processing array
        sync input port readImageAt: ExternalLibs.ReadImageAtIndex

        event ImageReadSuccess(index: U8) severity activity high format "ImageRead success - added at index {}"
        event ImageReadFailure(index: U8, status: ExternalLibs.ImageReadStatus) severity activity high format "ImageRead attempt for index {} resulted in {}"

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Port for sending textual representation of events
        text event port logTextOut

        @ Port for sending events to downlink
        event port logOut

        @ Port for sending command registrations
        command reg port cmdRegOut

        @ Port for receiving commands
        command recv port cmdIn

        @ Port for sending command responses
        command resp port cmdResponseOut
    }
}

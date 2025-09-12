module ExamplesDeployment {
    @ Generates a sine wave
    passive component Sine {
        @ Rate group input port
        sync input port run: Svc.Sched

        @ Output of sine(system time)
        telemetry Y: F64


        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Port for sending telemetry channels to downlink
        telemetry port tlmOut

    }
}
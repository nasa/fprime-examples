module ManagerWorker {
    @ A manager that leverages a worker component to do long-running work.
    active component Manager {

        @ Command to start the backround work
        async command START opcode 0

        @ Command to stop the background work
        async command STOP opcode 1

        @ Signal to start the worker
        output port startWorker: Fw.Signal

        @ Signal to cancel the worker
        @ TODO: is this reasonable? to have a cancel out and back
        output port cancelWorker: Fw.Signal

        @ Signal from the worker that the work is finished
        async input port doneRecv: Fw.CompletionStatus

        @ Ping input port to show that the manager remains responsive during work
        async input port pingIn: Svc.Ping

        @ Ping output port for response to the ping
        output port pingOut: Svc.Ping

        # Ensure the start and completion ports are wired to the same worker
        match startWorker with doneRecv

        # It is good practice to have events that announce when command dispatch has
        # been received by the component.

        @ Event to indicate that the work is starting
        event StartWork() severity activity high format "Manager starting work"

        @ Event to indicate that the work is stopping
        event StopWork() severity activity high format "Manager stopping work"

        @ Event to indicate that the work is done
        event WorkerDone() severity activity high format "Worker completed work"

        @ Event to indicate that the work was canceled
        event WorkerCanceled() severity activity high format "Worker canceled work"

        @ Event to indicate that the work failed
        event WorkerFailed() severity warning high format "Worker failed to do work"

        @ Event to indicate that the work is done
        event WorkerBusy() severity warning high format "Worker is currently busy"

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Port for sending command registrations
        command reg port cmdRegOut

        @ Port for receiving commands
        command recv port cmdIn

        @ Port for sending command responses
        command resp port cmdResponseOut

        @ Port for sending textual representation of events
        text event port logTextOut

        @ Port for sending events to downlink
        event port logOut

    }
}

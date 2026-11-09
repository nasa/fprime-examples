module FixedMessageLimit {
    @ Maximum number of schedIn messages the Processor holds on its queue
    constant MAX_PENDING = 3

    @ Upper bound on the demonstration processing time accepted by SET_PROCESSING_TIME
    constant MAX_PROCESSING_TIME_MS = 10000

    @ Processes rate group ticks on its own thread, holding at most MAX_PENDING ticks on its queue
    active component Processor {

        @ Rate group input. Runs on the rate group thread: claims a slot and queues one schedInInternal message.
        sync input port schedIn: Svc.Sched

        @ One message per admitted tick. The hook releases the slot when the queue is full.
        internal port schedInInternal hook

        @ Set the simulated per-tick processing time (demonstration only, 0 disables the delay)
        async command SET_PROCESSING_TIME(
            milliseconds: U32 @< Time spent processing each tick, 0 to MAX_PROCESSING_TIME_MS
        ) opcode 0

        @ A tick arrived while MAX_PENDING ticks were already pending and was skipped
        event TickSkipped(
            pending: U32 @< Pending ticks at the time of the skip
        ) \
            severity warning low id 0 \
            format "Tick skipped with {} ticks pending" \
            throttle 5

        @ A tick arrived while the component queue was full and was skipped
        event TickOverflow() \
            severity warning low id 1 \
            format "Tick skipped because the component queue was full" \
            throttle 5

        @ The processing time was changed
        event ProcessingTimeSet(
            milliseconds: U32 @< New processing time
        ) \
            severity activity low id 2 \
            format "Processing time set to {} ms"

        @ The requested processing time exceeds MAX_PROCESSING_TIME_MS
        event ProcessingTimeInvalid(
            milliseconds: U32 @< Requested processing time
            maximum: U32 @< Maximum allowed processing time
        ) \
            severity warning low id 3 \
            format "Processing time {} ms exceeds maximum {} ms"

        @ Number of ticks admitted onto the queue
        telemetry TicksAdmitted: U32 id 0

        @ Number of ticks skipped at the limit or on a full queue
        telemetry TicksSkipped: U32 id 1

        @ Number of ticks processed on the component thread
        telemetry TicksProcessed: U32 id 2

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

        @ Port for sending telemetry channels to downlink
        telemetry port tlmOut
    }
}

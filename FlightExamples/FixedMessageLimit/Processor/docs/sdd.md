# FixedMessageLimit::Processor

An active component demonstrating the
[Fixed Message Limit pattern](https://github.com/nasa/fprime/blob/devel/docs/user-manual/design-patterns/fixed-message-limit.md):
a repeating input (here the rate group tick on `schedIn`) is admitted onto the component queue at most
`FixedMessageLimit.MAX_PENDING` times. Ticks that arrive while `MAX_PENDING` ticks are already pending are skipped on the
rate group thread rather than queued, so the component's backlog of tick work is bounded regardless of how far behind it
falls. With `MAX_PENDING = 1` this collapses to the single queued message pattern.

## Design

`schedIn` is a `sync` input port, so its handler runs on the rate group thread. The handler claims a slot with an atomic
counter (`m_pending.fetch_add(1)`): if fewer than `MAX_PENDING` slots were claimed before this one, it queues one
`schedInInternal` message for the component thread; otherwise it releases the claim and skips the tick, emitting
`TickSkipped`. Because a message is queued only when the pre-increment count was below the limit, the queue never holds
more than `MAX_PENDING` of these messages. Concurrent callers can push the counter above the limit for an instant, which
can only produce a spurious skip, never an extra message.

The `schedInInternal` port is declared with the `hook` queue-full behavior. If the component queue is full of other
messages when a tick is admitted, `schedInInternal_overflowHook` runs on the rate group thread, releases the slot, and
emits `TickOverflow`. The internal handler releases the slot before it does its work, so a tick arriving during that
work can claim the freed slot.

## Processing time (demonstration only)

`SET_PROCESSING_TIME` sets a per-tick delay, bounded by `MAX_PROCESSING_TIME_MS`, that the internal handler sleeps for
on the component thread. This exists only so an operator can make the component fall behind its rate group on demand
and watch the limit take effect through `TickSkipped` events and the `TicksSkipped` channel. Flight components must not
block their thread this way; the delay stands in for a bounded unit of real work. Setting a new processing time clears
the throttle on `TickSkipped` and `TickOverflow` so each observation window reports its skips.

## Requirements

| Requirement | Description | Verification |
|---|---|---|
| FML-PROC-001 | The component shall accept a periodic schedule input on the caller's thread without blocking the caller. | Unit test |
| FML-PROC-002 | The component shall hold at most `MAX_PENDING` unprocessed schedule messages on its queue at any time, independent of other traffic on the queue. | Unit test |
| FML-PROC-003 | The component shall skip, rather than queue, a schedule input that arrives while `MAX_PENDING` messages are pending, count it, and emit a throttled `TickSkipped` event. | Unit test |
| FML-PROC-004 | The component shall release the pending slot when the message is dequeued, and when the queue rejects the message through the overflow hook, so that later inputs can be admitted. | Unit test |
| FML-PROC-005 | The component shall report `TicksAdmitted`, `TicksSkipped`, and `TicksProcessed` telemetry. | Unit test, integration test |
| FML-PROC-006 | The component shall accept `SET_PROCESSING_TIME` to set a demonstration-only per-tick processing delay of at most `MAX_PROCESSING_TIME_MS`, rejecting larger values with `VALIDATION_ERROR`. | Unit test, integration test |

## Interface

| Kind | Name | Description |
|---|---|---|
| `sync input` | `schedIn: Svc.Sched` | Rate group tick; claims a slot and queues one internal message |
| `internal` (`hook`) | `schedInInternal` | One message per admitted tick; hook releases the slot on a full queue |
| `async command` | `SET_PROCESSING_TIME(milliseconds: U32)` | Demonstration-only per-tick delay, 0 to `MAX_PROCESSING_TIME_MS` |
| `event` | `TickSkipped(pending: U32)` | Warning low, throttled: tick skipped at the limit |
| `event` | `TickOverflow()` | Warning low, throttled: tick skipped because the queue was full |
| `event` | `ProcessingTimeSet(milliseconds: U32)` | Activity low: processing time changed |
| `event` | `ProcessingTimeInvalid(milliseconds: U32, maximum: U32)` | Warning low: requested processing time rejected |
| `telemetry` | `TicksAdmitted: U32` | Ticks admitted onto the queue (includes ticks later rejected by the overflow hook) |
| `telemetry` | `TicksSkipped: U32` | Ticks skipped at the limit or by the overflow hook |
| `telemetry` | `TicksProcessed: U32` | Ticks processed on the component thread |

Telemetry is written from the internal handler, so the channels update each time a tick is processed.

## Observing the pattern from the GDS

With `fixedLimitProcessor` on the 1 Hz rate group in `ExamplesDeployment`:

1. Send `fixedLimitProcessor.SET_PROCESSING_TIME` with `milliseconds = 2500`. Each tick now takes 2.5 s while ticks
   arrive every second, so the backlog grows until `MAX_PENDING` ticks are pending.
2. Within a few seconds `TickSkipped` events report `pending = 3` and `TicksSkipped` climbs, while `TicksProcessed`
   continues to advance at the processing rate: the component is behind but its backlog is capped.
3. Send `SET_PROCESSING_TIME` with `milliseconds = 0`. The command is itself queued behind the pending slow ticks, so
   its response and `ProcessingTimeSet` arrive up to `MAX_PENDING` processing times later (about 7.5 s here). The queue
   then drains, `TickSkipped` stops, and every tick is processed again.

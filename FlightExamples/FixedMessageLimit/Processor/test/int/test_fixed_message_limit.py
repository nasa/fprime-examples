"""Integration tests for the FixedMessageLimit.Processor component

These tests expect the component to be driven by a rate group running at roughly 1 Hz, as `fixedLimitProcessor` is in
`ExamplesDeployment`. The processing time command is a demonstration-only control that makes the component fall behind
its rate group so the limit can be observed.
"""

import time

import pytest
from fprime_gds.common.testing_fw import predicates

# Fully qualified instance name in ExamplesDeployment; change to run against another deployment
INSTANCE = "ExamplesDeployment.fixedLimitProcessor"
MAX_PENDING = 3
MAX_PROCESSING_TIME_MS = 10000
# Each tick takes longer than two tick periods, so the backlog grows until the limit is reached
SLOW_PROCESSING_TIME_MS = 2500
# An async command waits behind up to MAX_PENDING slow ticks before the component processes it
SLOW_COMMAND_TIMEOUT = (MAX_PENDING + 1) * SLOW_PROCESSING_TIME_MS / 1000.0 + 5


def set_processing_time(fprime_test_api, milliseconds, timeout=SLOW_COMMAND_TIMEOUT):
    """Set the processing time and wait for the component to acknowledge it

    Processor is active, so its event races with the command dispatcher's completion event; assert both from the same
    starting point. The command is processed on the component thread, so it waits behind any pending slow ticks.
    """
    start = fprime_test_api.event_history.size()
    command = f"{INSTANCE}.SET_PROCESSING_TIME"
    command_id = fprime_test_api.translate_command_name(command)
    fprime_test_api.send_command(command, [milliseconds])
    fprime_test_api.assert_event(
        f"{INSTANCE}.ProcessingTimeSet", args=[milliseconds], start=start, timeout=timeout
    )
    fprime_test_api.assert_event("CdhCore.cmdDisp.OpCodeCompleted", args=[command_id], start=start, timeout=timeout)


@pytest.fixture(autouse=True)
def restore_processing_time(fprime_test_api):
    """Leave the component processing ticks at full speed after every test"""
    yield
    set_processing_time(fprime_test_api, 0)


def test_processing_time_rejected_above_maximum(fprime_test_api):
    """A processing time above MAX_PROCESSING_TIME_MS is rejected without changing the setting"""
    start = fprime_test_api.event_history.size()
    fprime_test_api.send_command(f"{INSTANCE}.SET_PROCESSING_TIME", [MAX_PROCESSING_TIME_MS + 1])
    fprime_test_api.assert_event(
        f"{INSTANCE}.ProcessingTimeInvalid",
        args=[MAX_PROCESSING_TIME_MS + 1, MAX_PROCESSING_TIME_MS],
        start=start,
        timeout=5,
    )
    fprime_test_api.assert_event("CdhCore.cmdDisp.OpCodeError", start=start, timeout=5)


def test_ticks_processed_when_keeping_up(fprime_test_api):
    """With no processing delay every tick is processed and none are skipped"""
    set_processing_time(fprime_test_api, 0)
    start = fprime_test_api.telemetry_history.size()
    event_start = fprime_test_api.event_history.size()
    first = fprime_test_api.await_telemetry(f"{INSTANCE}.TicksProcessed", start=start, timeout=5)
    assert first is not None, "TicksProcessed was not reported"
    # Three more ticks at roughly 1 Hz; the channel may be downlinked less often than it is written, so look for at least
    fprime_test_api.assert_telemetry(
        fprime_test_api.get_telemetry_pred(
            f"{INSTANCE}.TicksProcessed", predicates.greater_than_or_equal_to(first.get_val() + 3)
        ),
        start=start,
        timeout=10,
    )
    fprime_test_api.assert_event_count(0, f"{INSTANCE}.TickSkipped", start=event_start)


def test_backlog_limited_when_falling_behind(fprime_test_api):
    """A slow processing time fills MAX_PENDING slots, after which ticks are skipped at the limit, not queued"""
    set_processing_time(fprime_test_api, SLOW_PROCESSING_TIME_MS)
    event_start = fprime_test_api.event_history.size()

    # The backlog grows by less than one tick per period, so the first skip takes a few periods to appear
    skipped = fprime_test_api.assert_event(
        f"{INSTANCE}.TickSkipped", args=[MAX_PENDING], start=event_start, timeout=20
    )
    assert skipped.get_args()[0].val == MAX_PENDING, "Skip reported with an unexpected pending count"

    # The component keeps processing while behind: TicksProcessed advances and TicksSkipped is reported
    tlm_start = fprime_test_api.telemetry_history.size()
    processed = fprime_test_api.await_telemetry(f"{INSTANCE}.TicksProcessed", start=tlm_start, timeout=10)
    assert processed is not None, "TicksProcessed was not reported while behind"
    fprime_test_api.assert_telemetry(
        fprime_test_api.get_telemetry_pred(
            f"{INSTANCE}.TicksProcessed", predicates.greater_than_or_equal_to(processed.get_val() + 1)
        ),
        start=tlm_start,
        timeout=10,
    )
    skipped_tlm = fprime_test_api.await_telemetry(f"{INSTANCE}.TicksSkipped", start=tlm_start, timeout=10)
    assert skipped_tlm.get_val() >= 1, "TicksSkipped telemetry did not report the skip"

    # Back to full speed: the command itself waits behind the slow backlog, then the remaining ticks drain quickly
    set_processing_time(fprime_test_api, 0)
    time.sleep(2)
    quiet_start = fprime_test_api.event_history.size()
    time.sleep(3)
    fprime_test_api.assert_event_count(0, f"{INSTANCE}.TickSkipped", start=quiet_start)

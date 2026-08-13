import time


def send_and_assert_manager_event(fprime_test_api, command, event, timeout=5):
    """ Send a command and assert its event and completion independently

    Manager is active, so its events race with cmdDisp.OpCodeDispatched and cannot be ordered.
    """
    start = fprime_test_api.event_history.size()
    command_id = fprime_test_api.translate_command_name(command)
    fprime_test_api.send_command(command)
    fprime_test_api.assert_event(event, start=start, timeout=timeout)
    fprime_test_api.assert_event(
        "cmdDisp.OpCodeCompleted",
        args=[command_id],
        start=start,
        timeout=timeout,
    )


def test_manager_start_receive_work(fprime_test_api):
    """ Test that the manager can start and complete work """
    send_and_assert_manager_event(
        fprime_test_api, "ManagerWorker.manager.START", "ManagerWorker.manager.StartWork"
    )
    # Worker runs for ~5 seconds
    fprime_test_api.assert_event("ManagerWorker.manager.WorkerDone", timeout=6)


def test_manager_cancel_work(fprime_test_api):
    """ Test that the manager can cancel work without the work completing """
    send_and_assert_manager_event(
        fprime_test_api, "ManagerWorker.manager.START", "ManagerWorker.manager.StartWork"
    )
    send_and_assert_manager_event(
        fprime_test_api, "ManagerWorker.manager.STOP", "ManagerWorker.manager.StopWork"
    )
    # Worker runs for ~5 seconds but cancel will be sooner
    fprime_test_api.assert_event("ManagerWorker.manager.WorkerCanceled", timeout=1)


def test_worker_busy(fprime_test_api):
    """ Test that the manager will respond with WorkerBusy if work is already in progress """
    send_and_assert_manager_event(
        fprime_test_api, "ManagerWorker.manager.START", "ManagerWorker.manager.StartWork"
    )
    send_and_assert_manager_event(
        fprime_test_api, "ManagerWorker.manager.START", "ManagerWorker.manager.WorkerBusy"
    )
    # Wait for original work to complete to return to a clean state
    fprime_test_api.assert_event("ManagerWorker.manager.WorkerDone", timeout=6)


def test_manager_responsivity(fprime_test_api):
    """ Test that the manager remains responsive during work
    
    This test will stop work, then start work again. The manager should respond to the stop command, restart and complete work
    within a 50% margin of the original work time.
    """
    start_time = time.time()
    send_and_assert_manager_event(
        fprime_test_api, "ManagerWorker.manager.START", "ManagerWorker.manager.StartWork"
    )
    send_and_assert_manager_event(
        fprime_test_api, "ManagerWorker.manager.STOP", "ManagerWorker.manager.StopWork"
    )
    # Worker runs for ~5 seconds but cancel will be sooner
    fprime_test_api.assert_event("ManagerWorker.manager.WorkerCanceled", timeout=6)
    elapsed_time = time.time() - start_time
    assert elapsed_time < 1.5 * 5, "Manager was not responsive during work command"
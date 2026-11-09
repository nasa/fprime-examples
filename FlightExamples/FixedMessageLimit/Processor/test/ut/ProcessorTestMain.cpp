// ======================================================================
// \title  ProcessorTestMain.cpp
// \brief  cpp file for Processor component test main function
// ======================================================================

#include "ProcessorTester.hpp"

TEST(Nominal, TicksWithinLimit) {
    FixedMessageLimit::ProcessorTester tester;
    tester.test_ticks_within_limit();
}

TEST(Limit, TicksBeyondLimitSkipped) {
    FixedMessageLimit::ProcessorTester tester;
    tester.test_ticks_beyond_limit_skipped();
}

TEST(Limit, SlotReleasedAfterDispatch) {
    FixedMessageLimit::ProcessorTester tester;
    tester.test_slot_released_after_dispatch();
}

TEST(Limit, OverflowReleasesSlot) {
    FixedMessageLimit::ProcessorTester tester;
    tester.test_overflow_releases_slot();
}

TEST(Command, SetProcessingTime) {
    FixedMessageLimit::ProcessorTester tester;
    tester.test_set_processing_time();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

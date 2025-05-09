// ======================================================================
// \title  DecafDeframerTestMain.cpp
// \author thomas-bc
// \brief  cpp file for DecafDeframer component test main function
// ======================================================================

#include "DecafDeframerTester.hpp"
#include "STest/Random/Random.hpp"

TEST(DecafDeframer, NominalFrame) {
    Svc::DecafDeframerTester tester;
    tester.testNominalFrame();
}

TEST(DecafDeframer, TruncatedFrame) {
    Svc::DecafDeframerTester tester;
    tester.testTruncatedFrame();
}

TEST(DecafDeframer, ZeroSizeFrame) {
    Svc::DecafDeframerTester tester;
    tester.testZeroSizeFrame();
}

TEST(DecafDeframer, testIncorrectLengthToken) {
    Svc::DecafDeframerTester tester;
    tester.testIncorrectLengthToken();
}

TEST(DecafDeframer, testIncorrectStartWord) {
    Svc::DecafDeframerTester tester;
    tester.testIncorrectStartWord();
}

TEST(DecafDeframer, testIncorrectCrc) {
    Svc::DecafDeframerTester tester;
    tester.testIncorrectCrc();
}

TEST(DecafDeframer, testDataReturn) {
    Svc::DecafDeframerTester tester;
    tester.testDataReturn();
}

int main(int argc, char** argv) {
    STest::Random::seed();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

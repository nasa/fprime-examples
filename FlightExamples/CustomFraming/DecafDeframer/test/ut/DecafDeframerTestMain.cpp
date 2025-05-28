// ======================================================================
// \title  DecafDeframerTestMain.cpp
// \author thomas-bc
// \brief  cpp file for DecafDeframer component test main function
// ======================================================================

#include "DecafDeframerTester.hpp"
#include "STest/Random/Random.hpp"

TEST(DecafDeframer, NominalFrame) {
    CustomFraming::DecafDeframerTester tester;
    tester.testNominalFrame();
}

TEST(DecafDeframer, TruncatedFrame) {
    CustomFraming::DecafDeframerTester tester;
    tester.testTruncatedFrame();
}

TEST(DecafDeframer, ZeroSizeFrame) {
    CustomFraming::DecafDeframerTester tester;
    tester.testZeroSizeFrame();
}

TEST(DecafDeframer, testIncorrectLengthToken) {
    CustomFraming::DecafDeframerTester tester;
    tester.testIncorrectLengthToken();
}

TEST(DecafDeframer, testIncorrectStartWord) {
    CustomFraming::DecafDeframerTester tester;
    tester.testIncorrectStartWord();
}

TEST(DecafDeframer, testIncorrectCrc) {
    CustomFraming::DecafDeframerTester tester;
    tester.testIncorrectCrc();
}

TEST(DecafDeframer, testDataReturn) {
    CustomFraming::DecafDeframerTester tester;
    tester.testDataReturn();
}

int main(int argc, char** argv) {
    STest::Random::seed();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// ======================================================================
// \title  DecafFramerTestMain.cpp
// \author thomas-bc
// \brief  cpp file for DecafFramer component test main function
// ======================================================================

#include "DecafFramerTester.hpp"

TEST(Nominal, testComStatusPassThrough) {
    CustomFraming::DecafFramerTester tester;
    tester.testComStatusPassThrough();
}

TEST(Nominal, testFrameDeallocation) {
    CustomFraming::DecafFramerTester tester;
    tester.testFrameDeallocation();
}

TEST(Nominal, testNominalFraming) {
    CustomFraming::DecafFramerTester tester;
    tester.testNominalFraming();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

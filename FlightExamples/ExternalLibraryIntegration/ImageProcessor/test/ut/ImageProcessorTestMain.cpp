// ======================================================================
// \title  ImageProcessorTestMain.cpp
// \author chammard
// \brief  cpp file for ImageProcessor component test main function
// ======================================================================

#include "ImageProcessorTester.hpp"

TEST(Nominal, testReadImage) {
    ExternalLibraryIntegration::ImageProcessorTester tester;
    tester.testReadImage();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

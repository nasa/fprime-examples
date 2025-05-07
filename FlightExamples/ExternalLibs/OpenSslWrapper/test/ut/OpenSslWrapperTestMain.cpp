// ======================================================================
// \title  OpenSslWrapperTestMain.cpp
// \author thomas-bc
// \brief  cpp file for OpenSslWrapper component test main function
// ======================================================================

#include "OpenSslWrapperTester.hpp"

TEST(Nominal, testAesKeyRegistration) {
    ExternalLibs::OpenSslWrapperTester tester;
    tester.testAesKeyRegistration();
}

TEST(Nominal, testAesDecryption) {
    ExternalLibs::OpenSslWrapperTester tester;
    tester.testAesDecryption();
}

TEST(Nominal, testAesEncryption) {
    ExternalLibs::OpenSslWrapperTester tester;
    tester.testAesEncryption();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

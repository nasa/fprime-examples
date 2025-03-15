// ======================================================================
// \title  OpenSslWrapperTestMain.cpp
// \author chammard
// \brief  cpp file for OpenSslWrapper component test main function
// ======================================================================

#include "OpenSslWrapperTester.hpp"

TEST(Nominal, testAesKeyRegistration) {
    ExternalLibraryIntegration::OpenSslWrapperTester tester;
    tester.testAesKeyRegistration();
}

TEST(Nominal, testAesDecryption) {
    ExternalLibraryIntegration::OpenSslWrapperTester tester;
    tester.testAesDecryption();
}

TEST(Nominal, testAesEncryption) {
    ExternalLibraryIntegration::OpenSslWrapperTester tester;
    tester.testAesEncryption();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

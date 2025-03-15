// ======================================================================
// \title  OpenSslWrapperTester.hpp
// \author chammard
// \brief  hpp file for OpenSslWrapper component test harness implementation class
// ======================================================================

#ifndef ExternalLibraryIntegration_OpenSslWrapperTester_HPP
#define ExternalLibraryIntegration_OpenSslWrapperTester_HPP

#include "ExternalLibraryIntegration/OpenSslWrapper/OpenSslWrapper.hpp"
#include "ExternalLibraryIntegration/OpenSslWrapper/OpenSslWrapperGTestBase.hpp"

namespace ExternalLibraryIntegration {

class OpenSslWrapperTester final : public OpenSslWrapperGTestBase {
  public:
    // ----------------------------------------------------------------------
    // Constants
    // ----------------------------------------------------------------------

    // Maximum size of histories storing events, telemetry, and port outputs
    static const FwSizeType MAX_HISTORY_SIZE = 10;

    // Instance ID supplied to the component instance under test
    static const FwEnumStoreType TEST_INSTANCE_ID = 0;

  public:
    // ----------------------------------------------------------------------
    // Construction and destruction
    // ----------------------------------------------------------------------

    //! Construct object OpenSslWrapperTester
    OpenSslWrapperTester();

    //! Destroy object OpenSslWrapperTester
    ~OpenSslWrapperTester();

  public:
    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    //! Test AES key registration
    void testAesKeyRegistration();

    //! Test AES decryption with a known ciphertext-key-IV combination
    void testAesDecryption();

    //! Test AES decryption with a known ciphertext-key-IV combination
    void testAesEncryption();

  private:
    // ----------------------------------------------------------------------
    // Helper functions
    // ----------------------------------------------------------------------

    //! Connect ports
    void connectPorts();

    //! Initialize components
    void initComponents();

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The component under test
    OpenSslWrapper component;
    CryptoTypes::AesKeyType testAesKey;  //!< AES key for testing
};

}  // namespace ExternalLibraryIntegration

#endif

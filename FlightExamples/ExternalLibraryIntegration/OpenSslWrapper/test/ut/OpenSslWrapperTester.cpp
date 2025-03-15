// ======================================================================
// \title  OpenSslWrapperTester.cpp
// \author chammard
// \brief  cpp file for OpenSslWrapper component test harness implementation class
// ======================================================================

#include "OpenSslWrapperTester.hpp"

namespace ExternalLibraryIntegration {

// ----------------------------------------------------------------------
// Construction and destruction
// ----------------------------------------------------------------------

OpenSslWrapperTester ::OpenSslWrapperTester()
    : OpenSslWrapperGTestBase("OpenSslWrapperTester", OpenSslWrapperTester::MAX_HISTORY_SIZE),
      component("OpenSslWrapper") {
    this->initComponents();
    this->connectPorts();
    this->testAesKey = CryptoTypes::AesKeyType({
        0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77,
        0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77,
        0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77,
        0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77
    });
}

OpenSslWrapperTester ::~OpenSslWrapperTester() {}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void OpenSslWrapperTester ::testAesKeyRegistration() {
    this->clearEvents();

    // Register the AES key
    this->sendCmd_REGISTER_AES_KEY(0 ,0, this->testAesKey);
    ASSERT_EVENTS_SIZE(1); // Ensure exactly 1 event was logged
    ASSERT_EVENTS_SymmetricKeyRegistered_SIZE(1); // Ensure the event was SymmetricKeyRegistered

    ASSERT_EQ(this->component.m_aesKey, this->testAesKey); // Ensure the key was registered correctly
}

void OpenSslWrapperTester ::testAesDecryption() {
    // Use online encryptor such as https://cryptii.com/pipes/aes-encryption
    // We are using a known ciphertext + key + IV for testing purposes
    U8 iv_data[16] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};
    U8 decrypted_data[8] = {0xFF, 0xFF, 0xFF, 0xFF,0xFF, 0xFF, 0xFF, 0xFF};
    this->component.m_aesKey = this->testAesKey;
    // Encrypting with the above settings gives the below ciphertext. We are testing the reverse operation
    // to ensure the decryption works as expected.
    U8 encrypted_data[8] = {0x98, 0xe2, 0xe7, 0x21, 0xcf, 0xcb, 0xc7, 0xbc};

    // Test AES decryption with a known ciphertext and IV (16 bytes each)
    Fw::Buffer iv(iv_data, sizeof(iv_data)); 
    Fw::Buffer encrypted_buff(encrypted_data, sizeof(encrypted_data));
    // Decrypt in place by invoking the aesDecryptIn handler
    CryptoTypes::DecryptStatus status = this->invoke_to_aesDecryptIn(0, 0, iv, encrypted_buff);
    
    // Assert the decryption status and check the decrypted data
    ASSERT_EQ(status, CryptoTypes::DecryptStatus::OK);
    // printf("Decrypted data: ");
    for (size_t i = 0; i < sizeof(decrypted_data); ++i) {
        // printf("%02x ", encrypted_buff.getData()[i]);
        ASSERT_EQ(encrypted_buff.getData()[i], decrypted_data[i]); // Ensure decrypted data matches expected
    }
    // printf("\n");

}

void OpenSslWrapperTester ::testAesEncryption() {
  // Use online encryptor such as https://cryptii.com/pipes/aes-encryption
  // We are using a known ciphertext + key + IV for testing purposes
  U8 iv_data[16] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};
  U8 decrypted_data[8] = {0xFF, 0xFF, 0xFF, 0xFF,0xFF, 0xFF, 0xFF, 0xFF};
  this->component.m_aesKey = this->testAesKey;
  // Encrypting with the above settings gives the below ciphertext. We are testing the reverse operation
  // to ensure the encryption works as expected.
  U8 encrypted_data[8] = {0x98, 0xe2, 0xe7, 0x21, 0xcf, 0xcb, 0xc7, 0xbc};

  // Test AES encryption with a known ciphertext and IV (16 bytes each)
  Fw::Buffer iv(iv_data, sizeof(iv_data)); 
  Fw::Buffer decrypted_buff(decrypted_data, sizeof(decrypted_data));
  // Decrypt in place by invoking the aesDecryptIn handler
  CryptoTypes::DecryptStatus status = this->invoke_to_aesEncryptIn(0, 0, iv, decrypted_buff);
  
  // Assert the encryption status and check the decrypted data
  ASSERT_EQ(status, CryptoTypes::DecryptStatus::OK);
  // printf("Decrypted data: ");
  for (size_t i = 0; i < sizeof(decrypted_data); ++i) {
      // printf("%02x ", decrypted_buff.getData()[i]);
      ASSERT_EQ(decrypted_buff.getData()[i], encrypted_data[i]); // Ensure decrypted data matches expected
  }
  // printf("\n");

}

}  // namespace ExternalLibraryIntegration

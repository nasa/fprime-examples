// ======================================================================
// \title  OpenSslWrapper.hpp
// \author thomas-bc
// \brief  hpp file for OpenSslWrapper component implementation class
// ======================================================================

#ifndef ExternalLibraryIntegration_OpenSslWrapper_HPP
#define ExternalLibraryIntegration_OpenSslWrapper_HPP

#define OPENSSL_API_COMPAT 30100 // this is openssl v3.1.0

#include <openssl/evp.h>

#include "ExternalLibraryIntegration/OpenSslWrapper/OpenSslWrapperComponentAc.hpp"

namespace ExternalLibraryIntegration {

class OpenSslWrapper : public OpenSslWrapperComponentBase {
  public:
    static const U32 AES_KEY_SIZE = 32;

    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct OpenSslWrapper object
    OpenSslWrapper(const char* const compName  //!< The component name
    );

    //! Destroy OpenSslWrapper object
    ~OpenSslWrapper();

  PRIVATE:
    // ----------------------------------------------------------------------
    // Handler implementations for user-defined typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for aesDecryptIn
    CryptoTypes::DecryptStatus aesDecryptIn_handler(
        FwIndexType portNum,        //!< The port number
        U16 sa_id,                  //!< Security Association (SPI)
        Fw::Buffer& iv,             //!< Initialization Vector
        Fw::Buffer& encrypted_buff  //!< Encrypted buffer to decrypt (decrypted in place with AES)
        ) override;

    //! Handler implementation for aesEncryptIn
    CryptoTypes::DecryptStatus aesEncryptIn_handler(
      FwIndexType portNum,        //!< The port number
      U16 sa_id,                  //!< Security Association (SPI)
      Fw::Buffer& iv,             //!< Initialization Vector
      Fw::Buffer& encrypted_buff  //!< Encrypted buffer to decrypt (decrypted in place with AES)
      ) override;

  PRIVATE:
    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command REGISTER_AES_KEY
    //!
    //! Register a new symmetric key with Security Association (SA) sa_id
    void REGISTER_AES_KEY_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                                     U32 cmdSeq,           //!< The command sequence number
                                     CryptoTypes::AesKeyType key) override;

    //! Handler implementation for command DEREGISTER_AES_KEY
    //!
    //! Register a new symmetric key with Security Association (SA) sa_id
    void DEREGISTER_AES_KEY_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                                     U32 cmdSeq           //!< The command sequence number
                                     ) override;


    // ----------------------------------------------------------------------
    // Helpers
    // ----------------------------------------------------------------------
  PRIVATE:
    // Decrypt buffer in place and return length of decrypted buffer
    FwSizeType aes_decrypt(U8* buffer,
                           FwSizeType buffer_len,
                           const U8* key,
                           const U8* iv,
                           EVP_CIPHER_CTX* ctx,
                           EVP_CIPHER* cipher);

    // Encrypt buffer in place and return length of encrypted buffer
    FwSizeType aes_encrypt(U8* buffer,
                           FwSizeType buffer_len,
                           const U8* key,
                           const U8* iv,
                           EVP_CIPHER_CTX* ctx,
                           EVP_CIPHER* cipher);

    // Register a new AES Key
    void registerAesKey(CryptoTypes::AesKeyType key);

    // Get the AES key in raw bytes (U8*)
    U8* getAesKey();
  
  PRIVATE:
    // AES Key type to transmit over the wire (unsafe without asymetric encryption)
    CryptoTypes::AesKeyType m_aesKey;  // U8[32] (defined in FPP)
    // OpenSSL types for AES methods
    EVP_CIPHER* m_cipherMethod;
    EVP_CIPHER_CTX* m_cipherCtx;
};

}  // namespace ExternalLibraryIntegration

#endif

// ======================================================================
// \title  OpenSslWrapper.cpp
// \author thomas-bc
// \brief  cpp file for OpenSslWrapper component implementation class
// ======================================================================

#include "ExternalLibraryIntegration/OpenSslWrapper/OpenSslWrapper.hpp"
#include "Fw/Logger/Logger.hpp"

namespace ExternalLibraryIntegration {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

OpenSslWrapper ::OpenSslWrapper(const char* const compName) : OpenSslWrapperComponentBase(compName) {
    // Initialize AES context objects
    this->m_cipherCtx = EVP_CIPHER_CTX_new();
    // Using AES-256-CTR cipher
    this->m_cipherMethod = EVP_CIPHER_fetch(NULL, "AES-256-CTR", NULL);
}

OpenSslWrapper ::~OpenSslWrapper() {
    EVP_CIPHER_free(this->m_cipherMethod);
    EVP_CIPHER_CTX_free(this->m_cipherCtx);
}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

CryptoTypes::DecryptStatus OpenSslWrapper ::aesDecryptIn_handler(FwIndexType portNum,
                                                                 U16 sa_id,
                                                                 Fw::Buffer& iv,
                                                                 Fw::Buffer& in_buffer) {
    CryptoTypes::DecryptStatus status = CryptoTypes::DecryptStatus::ERROR;
    // Decrypt with AES and symmetric key
    aes_decrypt(in_buffer.getData(), in_buffer.getSize(), &this->m_aesKey[0], iv.getData(), this->m_cipherCtx,
                this->m_cipherMethod);
    status = CryptoTypes::DecryptStatus::OK;

    return status;
}

CryptoTypes::DecryptStatus OpenSslWrapper ::aesEncryptIn_handler(FwIndexType portNum,
                                                                 U16 sa_id,
                                                                 Fw::Buffer& iv,
                                                                 Fw::Buffer& in_buffer) {
    CryptoTypes::DecryptStatus status = CryptoTypes::DecryptStatus::ERROR;
    // Decrypt with AES and symmetric key
    aes_encrypt(in_buffer.getData(), in_buffer.getSize(), &this->m_aesKey[0], iv.getData(), this->m_cipherCtx,
                this->m_cipherMethod);
    status = CryptoTypes::DecryptStatus::OK;

    return status;
}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void OpenSslWrapper ::REGISTER_AES_KEY_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                                                  U32 cmdSeq,           //!< The command sequence number
                                                  CryptoTypes::AesKeyType key) {
    this->registerAesKey(key);
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void OpenSslWrapper ::DEREGISTER_AES_KEY_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                                                    U32 cmdSeq) {         //!< The command sequence number
    this->m_aesKey = CryptoTypes::AesKeyType(0);
    this->log_ACTIVITY_HI_SymmetricKeyDeregistered(1);
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

// ----------------------------------------------------------------------
// Helpers
// ----------------------------------------------------------------------

FwSizeType OpenSslWrapper::aes_encrypt(U8* buffer,
                                       FwSizeType buffer_len,
                                       const U8* key,
                                       const U8* iv,
                                       EVP_CIPHER_CTX* ctx,
                                       EVP_CIPHER* cipher) const {
    PlatformIntType len;
    PlatformIntType ciphertext_len;

    if (EVP_CIPHER_CTX_reset(ctx) != 1) {
        Fw::Logger::log("[WARNING] EVP_CIPHER_CTX_reset failed\n");
        return 0;
    }

    if (EVP_EncryptInit_ex2(ctx, cipher, key, iv, NULL) != 1) {
        Fw::Logger::log("[WARNING] EVP_EncryptInit_ex2 failed\n");
        return 0;
    }

    if (EVP_EncryptUpdate(ctx, buffer, &len, buffer, buffer_len) != 1) {
        Fw::Logger::log("[WARNING] EVP_EncryptUpdate failed\n");
        return 0;
    }
    ciphertext_len = len;

    if (EVP_EncryptFinal_ex(ctx, buffer + len, &len) != 1) {
        Fw::Logger::log("[WARNING] EVP_EncryptFinal_ex failed\n");
        return 0;
    }
    ciphertext_len += len;

    return ciphertext_len;
}

FwSizeType OpenSslWrapper::aes_decrypt(U8* buffer,
                                       FwSizeType buffer_len,
                                       const U8* key,
                                       const U8* iv,
                                       EVP_CIPHER_CTX* ctx,
                                       EVP_CIPHER* cipher) const {
    PlatformIntType outlen;
    PlatformIntType plaintext_len;

    if (EVP_CIPHER_CTX_reset(ctx) != 1) {
        Fw::Logger::log("[WARNING] EVP_CIPHER_CTX_reset failed\n");
        return 0;
    }

    if (EVP_DecryptInit_ex2(ctx, cipher, key, iv, NULL) != 1) {
        Fw::Logger::log("[WARNING] EVP_DecryptInit_ex2 failed\n");
        return 0;
    }

    if (EVP_DecryptUpdate(ctx, buffer, &outlen, buffer, buffer_len) != 1) {
        Fw::Logger::log("[WARNING] EVP_DecryptUpdate failed\n");
        return 0;
    }
    plaintext_len = outlen;

    if (EVP_DecryptFinal_ex(ctx, buffer + outlen, &outlen) != 1) {
        Fw::Logger::log("[WARNING] EVP_DecryptFinal_ex failed\n");
        return 0;
    }
    plaintext_len += outlen;

    return plaintext_len;
}

void OpenSslWrapper::registerAesKey(CryptoTypes::AesKeyType key) {
    FW_ASSERT(key.SIZE == this->AES_KEY_SIZE, key.SIZE);
    this->m_aesKey = key;
    this->log_ACTIVITY_HI_SymmetricKeyRegistered(1);
}

}  // namespace ExternalLibraryIntegration

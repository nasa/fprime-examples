module CryptoTypes {

    array AesKeyType = [32] U8

    enum DecryptStatus {
        OK,
        ERROR,
    }

    enum AesSessionStatus {
        OK,
        ERROR
    }

    @ Port for decryption with AES
    port AesEncryptDecrypt(
        sa_id: U16,                    @< Security Association (SPI)
        ref iv: Fw.Buffer,             @< Initialization Vector
        ref encrypted_buff: Fw.Buffer  @< Encrypted buffer to decrypt (decrypted in place with AES)
    ) -> DecryptStatus

    @ Port to register an AES Key
    port AesKeyRegistration(
        key: AesKeyType,               @< Symmetric key to register (16 bytes - 256 bits)
    ) -> AesSessionStatus


}

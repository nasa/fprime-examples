module ExternalLibraryIntegration {

    enum ImageReadStatus {
        OK,
        INVALID_INDEX,
        OTHER_ERROR,
    }

    @ Port for decryption with AES
    port ReadImageAtIndex(
        index: U8,                    @< Index to insert the image at in the 
        onboardPath: string,          @< Path to onboard image to read
    ) -> ImageReadStatus


}

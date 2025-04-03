module ExternalLibraryIntegration {

    @ Component for F Prime FSW framework.
    passive component OpenSslWrapper {

        @ Register a new AES key
        sync command REGISTER_AES_KEY(key: AesKeyType) opcode 0
        @ De-register the current AES key (effectively ends the session)
        sync command DEREGISTER_AES_KEY() opcode 1

        @ Perform AES encryption
        sync input port aesEncryptIn: AesEncryptDecrypt

        @ Perform AES decryption
        sync input port aesDecryptIn: AesEncryptDecrypt

        @ New AES key has been registered, starts the AES session
        event SymmetricKeyRegistered(sa_id: U16) severity activity high format "New AES session - key registered with SA id {}"
        @ AES key de-registered, ends the AES session
        event SymmetricKeyDeregistered(sa_id: U16) severity activity high format "AES session ended for SA id {}"

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Port for sending command registrations
        command reg port cmdRegOut

        @ Port for receiving commands
        command recv port cmdIn

        @ Port for sending command responses
        command resp port cmdResponseOut

        @ Port for sending textual representation of events
        text event port logTextOut

        @ Port for sending events to downlink
        event port logOut

        @ Port for sending telemetry channels to downlink
        telemetry port tlmOut

    }
}

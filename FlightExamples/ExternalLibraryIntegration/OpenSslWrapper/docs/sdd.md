# ExternalLibraryIntegration::OpenSslWrapper

The OpenSslWrapper component provides a wrapper around the OpenSSL library and exposes some of the library's functionality to the rest of the F´ application.

The current implementation provides an interface to AES encryption functionality. The component provides a command to register an AES key. It also provides two ports, one for receiving AES encryption requests, and another for decrption requests. Once an AES key is registered, other components of the system can request from the OpenSslWrapper to encrypt and decrypt data using the OpenSSL AES algorithms.

## Port Descriptions

| Name | Description |
|---|---|
| `sync input port aesEncryptIn` | Input port for AES encryption requests. This port receives data to be encrypted along with the Initialization Vector (IV) |
| `sync input port aesDecryptIn` | Input port for AES decryption requests. This port receives data to be decrypted along with the Initialization Vector (IV) |

## Commands

| Name | Description |
|---|---|
| `REGISTER_AES_KEY` | Register a new symmetric key for the component to use for future encryption/decryption requests |
| `DEREGISTER_AES_KEY` | Deregister the current symmetric key to prevent further encryption/decryption requests |

## Events

| Name | Description |
|---|---|
| `SymmetricKeyRegistered` | A new symmetric key has been registered with the OpenSslWrapper. |
| `SymmetricKeyDeregistered` | The registered symmetric key has been de-registered from the OpenSslWrapper. |

## Requirements

| Name | Description | Validation |
|---|---|---|
| LIBS-OPENSSLWRAPPER-001 | The `OpenSslWrapper` shall provide a mechanism for the ground to register AES keys to be used for subsequent encryption and decryption. | Unit tests |
| LIBS-OPENSSLWRAPPER-001 | The `OpenSslWrapper` shall provide a mechanism for the ground to de-register an AES keys to prevent further encryption or decryption | Unit tests |
| LIBS-OPENSSLWRAPPER-001 | The `OpenSslWrapper` shall provide a port for components to request encryption of a provided data and IV, using a pre-registered key | Unit tests |
| LIBS-OPENSSLWRAPPER-001 | The `OpenSslWrapper` shall provide a port for components to request decryption of a provided data and IV, using a pre-registered key | Unit tests |

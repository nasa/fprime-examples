// ======================================================================
// \title  OpenSslWrapper.cpp
// \author chammard
// \brief  cpp file for OpenSslWrapper component implementation class
// ======================================================================

#include "ExternalLibraryIntegration/OpenSslWrapper/OpenSslWrapper.hpp"

namespace ExternalLibraryIntegration {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  OpenSslWrapper ::
    OpenSslWrapper(const char* const compName) :
      OpenSslWrapperComponentBase(compName)
  {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_CIPHER_CTX_free(ctx);
  }

  OpenSslWrapper ::
    ~OpenSslWrapper()
  {

  }

}

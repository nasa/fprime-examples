// ======================================================================
// \title  OpenSslWrapper.hpp
// \author chammard
// \brief  hpp file for OpenSslWrapper component implementation class
// ======================================================================

#ifndef ExternalLibraryIntegration_OpenSslWrapper_HPP
#define ExternalLibraryIntegration_OpenSslWrapper_HPP

#include "ExternalLibraryIntegration/OpenSslWrapper/OpenSslWrapperComponentAc.hpp"
#include <openssl/evp.h>

namespace ExternalLibraryIntegration {

  class OpenSslWrapper :
    public OpenSslWrapperComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Component construction and destruction
      // ----------------------------------------------------------------------

      //! Construct OpenSslWrapper object
      OpenSslWrapper(
          const char* const compName //!< The component name
      );

      //! Destroy OpenSslWrapper object
      ~OpenSslWrapper();

  };

}

#endif

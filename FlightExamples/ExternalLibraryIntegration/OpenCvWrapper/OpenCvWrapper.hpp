// ======================================================================
// \title  OpenCvWrapper.hpp
// \author thomas-bc
// \brief  hpp file for OpenCvWrapper component implementation class
// ======================================================================

#ifndef ExternalLibraryIntegration_OpenCvWrapper_HPP
#define ExternalLibraryIntegration_OpenCvWrapper_HPP

#include "ExternalLibraryIntegration/OpenCvWrapper/OpenCvWrapperComponentAc.hpp"

namespace ExternalLibraryIntegration {

  class OpenCvWrapper :
    public OpenCvWrapperComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Component construction and destruction
      // ----------------------------------------------------------------------

      //! Construct OpenCvWrapper object
      OpenCvWrapper(
          const char* const compName //!< The component name
      );

      //! Destroy OpenCvWrapper object
      ~OpenCvWrapper();

  };

}

#endif

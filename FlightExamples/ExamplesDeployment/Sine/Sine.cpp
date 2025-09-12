// ======================================================================
// \title  Sine.cpp
// \author mstarch
// \brief  cpp file for Sine component implementation class
// ======================================================================

#include "ExamplesDeployment/Sine/Sine.hpp"
#include <cmath>

namespace ExamplesDeployment {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

Sine ::Sine(const char* const compName) : SineComponentBase(compName) {}

Sine ::~Sine() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void Sine ::run_handler(FwIndexType portNum, U32 context) {
    Fw::Time now = this->getTime();
    F64 time_in_seconds = static_cast<F64>(now.getSeconds()) + (static_cast<F64>(now.getUSeconds()) / 1000000.0);
    this->tlmWrite_Y(sin(time_in_seconds), now);
}

}  // namespace ExamplesDeployment

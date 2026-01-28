// ======================================================================
// \title  ExamplesDeploymentTopologyDefs.hpp
// \brief required header file containing the required definitions for the topology autocoder
//
// ======================================================================
#ifndef ExamplesDeployment_ExamplesDeploymentTOPOLOGYDEFS_HPP
#define ExamplesDeployment_ExamplesDeploymentTOPOLOGYDEFS_HPP

// Subtopology PingEntries includes
#include "Svc/Subtopologies/CdhCore/PingEntries.hpp"
#include "Svc/Subtopologies/DataProducts/PingEntries.hpp"
#include "Svc/Subtopologies/FileHandling/PingEntries.hpp"

// SubtopologyTopologyDefs includes
#include "Svc/Subtopologies/CdhCore/SubtopologyTopologyDefs.hpp"
#include "Svc/Subtopologies/DataProducts/SubtopologyTopologyDefs.hpp"
#include "Svc/Subtopologies/FileHandling/SubtopologyTopologyDefs.hpp"

#include "ExternalLibs/Subtopology/ExternalLibsTopologyDefs.hpp"
#include "ManagerWorker/Subtopology/ManagerWorkerTopologyDefs.hpp"

// Include autocoded FPP constants
#include "ExamplesDeployment/Top/FppConstantsAc.hpp"
#include "ExamplesDeployment/Top/Ports_ComBufferQueueEnumAc.hpp"
#include "ExamplesDeployment/Top/Ports_ComPacketQueueEnumAc.hpp"

// Include required headers for phased code
#include "Fw/Time/TimeInterval.hpp"
#include "Svc/FrameAccumulator/FrameDetector/FprimeFrameDetector.hpp"

/**
 * \brief required ping constants
 *
 * The topology autocoder requires a WARN and FATAL constant definition for each component that supports the health-ping
 * interface. These are expressed as enum constants placed in a namespace named for the component instance. These
 * are all placed in the PingEntries namespace.
 *
 * Each constant specifies how many missed pings are allowed before a WARNING_HI/FATAL event is triggered. In the
 * following example, the health component will emit a WARNING_HI event if the component instance cmdDisp does not
 * respond for 3 pings and will FATAL if responses are not received after a total of 5 pings.
 *
 * ```c++
 * namespace PingEntries {
 * namespace cmdDisp {
 *     enum { WARN = 3, FATAL = 5 };
 * }
 * }
 * ```
 */
namespace PingEntries {
namespace ExamplesDeployment_rateGroup1 {
enum { WARN = 3, FATAL = 5 };
}
namespace ExamplesDeployment_rateGroup2 {
enum { WARN = 3, FATAL = 5 };
}
namespace ExamplesDeployment_rateGroup3 {
enum { WARN = 3, FATAL = 5 };
}
namespace ExamplesDeployment_cmdSeq {
enum { WARN = 3, FATAL = 5 };
}
}  // namespace PingEntries

// Definitions are placed within a namespace named after the deployment
namespace ExamplesDeployment {

/**
 * \brief required type definition to carry state
 *
 * The topology autocoder requires an object that carries state with the name `ExamplesDeployment::TopologyState`. Only
 * the type definition is required by the autocoder and the contents of this object are otherwise opaque to the
 * autocoder. The contents are entirely up to the definition of the project. This deployment uses subtopologies.
 */
struct TopologyState {
    const char* hostname;                         //!< Hostname for TCP communication
    U16 port;                                     //!< Port for TCP communication
    CdhCore::SubtopologyState cdhCore;            //!< Subtopology state for CdhCore
    FileHandling::SubtopologyState fileHandling;  //!< Subtopology state for FileHandling
};

namespace PingEntries = ::PingEntries;
}  // namespace ExamplesDeployment
#endif

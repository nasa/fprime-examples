// ======================================================================
// \title  ExamplesDeploymentTopologyDefs.hpp
// \brief required header file containing the required definitions for the topology autocoder
//
// ======================================================================
#ifndef EXAMPLESDEPLOYMENT_EXAMPLESDEPLOYMENTTOPOLOGYDEFS_HPP
#define EXAMPLESDEPLOYMENT_EXAMPLESDEPLOYMENTTOPOLOGYDEFS_HPP

#include "Fw/Types/MallocAllocator.hpp"
#include "ExamplesDeployment/Top/FppConstantsAc.hpp"
#include "Svc/FramingProtocol/FprimeProtocol.hpp"
#include "Svc/Health/Health.hpp"

// Subtopology includes
#include <ManagerWorker/Subtopology/ManagerWorkerTopologyDefs.hpp>
#include <ExternalLibs/Subtopology/ExternalLibsTopologyDefs.hpp>

// Definitions are placed within a namespace named after the deployment
namespace ExamplesDeployment {

/**
 * \brief required type definition to carry state
 *
 * The topology autocoder requires an object that carries state with the name `ExamplesDeployment::TopologyState`. Only the type
 * definition is required by the autocoder and the contents of this object are otherwise opaque to the autocoder. The contents are entirely up
 * to the definition of the project. Here, they are derived from command line inputs.
 */
struct TopologyState {
    const CHAR* hostname;
    U16 port;
    ManagerWorker::ManagerWorkerState ManagerWorker_state;
    ExternalLibs::ExternalLibsState ExternalLibs_state;
};

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
namespace PingEntries = GlobalDefs::PingEntries;
} // namespace ExamplesDeployment

namespace GlobalDefs {
namespace PingEntries {
namespace ExamplesDeployment_blockDrv {
enum { WARN = 3, FATAL = 5 };
}
namespace ExamplesDeployment_tlmSend {
enum { WARN = 3, FATAL = 5 };
}
namespace ExamplesDeployment_cmdDisp {
enum { WARN = 3, FATAL = 5 };
}
namespace ExamplesDeployment_cmdSeq {
enum { WARN = 3, FATAL = 5 };
}
namespace ExamplesDeployment_eventLogger {
enum { WARN = 3, FATAL = 5 };
}
namespace ExamplesDeployment_fileDownlink {
enum { WARN = 3, FATAL = 5 };
}
namespace ExamplesDeployment_fileManager {
enum { WARN = 3, FATAL = 5 };
}
namespace ExamplesDeployment_fileUplink {
enum { WARN = 3, FATAL = 5 };
}
namespace ExamplesDeployment_prmDb {
enum { WARN = 3, FATAL = 5 };
}
namespace ExamplesDeployment_rateGroup1 {
enum { WARN = 3, FATAL = 5 };
}
namespace ExamplesDeployment_rateGroup2 {
enum { WARN = 3, FATAL = 5 };
}
namespace ExamplesDeployment_rateGroup3 {
enum { WARN = 3, FATAL = 5 };
}
}  // namespace PingEntries
}  // namespace GlobalDefs
#endif

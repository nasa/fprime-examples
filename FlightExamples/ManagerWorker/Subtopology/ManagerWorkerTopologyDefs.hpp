#ifndef MANAGERWORKERSUBTOPOLOGY_DEFS_HPP
#define MANAGERWORKERSUBTOPOLOGY_DEFS_HPP

namespace ManagerWorker {
struct ManagerWorkerState {
    /* include any variables that are needed for
    configuring/starting/tearing down the topology */
};
}  // namespace ManagerWorker

namespace PingEntries {
namespace ManagerWorker_manager {
enum { WARN = 3, FATAL = 5 };
}
}  // namespace PingEntries

#endif
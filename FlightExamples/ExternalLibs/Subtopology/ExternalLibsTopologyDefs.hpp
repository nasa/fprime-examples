#ifndef ExternalLibsSUBTOPOLOGY_DEFS_HPP
#define ExternalLibsSUBTOPOLOGY_DEFS_HPP

namespace ExternalLibs {
    struct ExternalLibsState {
        /* include any variables that are needed for 
        configuring/starting/tearing down the topology */
    };
    struct TopologyState {
        ExternalLibsState ExternalLibs_state;
    };
}

namespace GlobalDefs {
    namespace PingEntries {
        namespace ExternalLibs_manager {
            enum {
                WARN = 3,
                FATAL = 5
            };
        }
    }
}

#endif
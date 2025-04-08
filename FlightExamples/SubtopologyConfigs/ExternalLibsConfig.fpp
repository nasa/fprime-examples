module ExternalLibsSubtopologyConfig {
    # Base ID for your subtopology. All instantiated components will be offsets of this
    constant ExternalLibsSubtopology_BASE_ID = 0xFFEE0000
    
    # No defaults and priorities needed, all components are passive
    # module Defaults {
    #     constant QUEUE_SIZE = 10
    #     constant STACK_SIZE = 64 * 1024
    # }

    # module Priorities {
    #      constant openSslWrapper = 90
    #      constant imageProcessor = 30
    # }
}

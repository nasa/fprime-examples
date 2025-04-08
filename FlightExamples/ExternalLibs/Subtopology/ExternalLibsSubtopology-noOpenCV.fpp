module ExternalLibs {

    instance openSslWrapper: ExternalLibs.OpenSslWrapper base id ExternalLibsSubtopologyConfig.ExternalLibsSubtopology_BASE_ID + 0x0000 \
        queue size ExternalLibs.Defaults.QUEUE_SIZE \
        stack size ExternalLibs.Defaults.STACK_SIZE \
        priority ExternalLibs.Priorities.openSslWrapper

    @ Subtopology for ExternalLibs components
    topology Subtopology {
        instance openSslWrapper
    } # end topology
} # end ExternalLibsSubtopology

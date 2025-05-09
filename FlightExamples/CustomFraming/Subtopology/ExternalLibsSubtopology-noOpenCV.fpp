module ExternalLibs {

    instance openSslWrapper: ExternalLibs.OpenSslWrapper base id ExternalLibsSubtopologyConfig.ExternalLibsSubtopology_BASE_ID + 0x0000

    @ Subtopology for ExternalLibs components
    topology Subtopology {
        instance openSslWrapper
    } # end topology
} # end ExternalLibsSubtopology

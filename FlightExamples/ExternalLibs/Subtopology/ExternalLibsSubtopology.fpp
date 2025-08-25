module ExternalLibs {

    instance openSslWrapper: ExternalLibs.OpenSslWrapper base id ExternalLibsSubtopologyConfig.ExternalLibsSubtopology_BASE_ID + 0x0000

    instance imageProcessor: ExternalLibs.ImageProcessor base id ExternalLibsSubtopologyConfig.ExternalLibsSubtopology_BASE_ID + 0x1000

    @ Subtopology for ExternalLibs components
    topology Subtopology {
        instance openSslWrapper
        instance imageProcessor
    } # end topology
} # end ExternalLibsSubtopology

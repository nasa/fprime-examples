telemetry packets ExamplesDeploymentPackets {

  packet CDH id 1 group 1 {
    CdhCore.cmdDisp.CommandsDispatched
    CdhCore.cmdDisp.CommandsDropped

    FileHandling.fileUplink.FilesReceived
    FileHandling.fileUplink.PacketsReceived
    FileHandling.fileDownlink.FilesSent
    FileHandling.fileDownlink.PacketsSent
    FileHandling.fileManager.CommandsExecuted

    ExamplesDeployment.cmdSeq.CS_LoadCommands
    ExamplesDeployment.cmdSeq.CS_CancelCommands
    ExamplesDeployment.cmdSeq.CS_CommandsExecuted
    ExamplesDeployment.cmdSeq.CS_SequencesCompleted
    ExamplesDeployment.comQueue.comQueueDepth
    ExamplesDeployment.comQueue.buffQueueDepth
    ExamplesDeployment.commsBufferManager.TotalBuffs
    ExamplesDeployment.commsBufferManager.CurrBuffs
    ExamplesDeployment.commsBufferManager.HiBuffs
    CdhCore.tlmSend.GroupConfigs
    CdhCore.tlmSend.SectionEnabled

    ExamplesDeployment.rateGroup1.RgMaxTime
    ExamplesDeployment.rateGroup2.RgMaxTime
    ExamplesDeployment.rateGroup3.RgMaxTime
  }

  packet CDHErrors id 2 group 1 {
    CdhCore.$health.PingLateWarnings

    FileHandling.fileUplink.Warnings
    FileHandling.fileDownlink.Warnings
    FileHandling.fileManager.Errors

    ExamplesDeployment.cmdSeq.CS_Errors
    ExamplesDeployment.commsBufferManager.NoBuffs
    ExamplesDeployment.commsBufferManager.EmptyBuffs

    ExamplesDeployment.rateGroup1.RgCycleSlips
    ExamplesDeployment.rateGroup2.RgCycleSlips
    ExamplesDeployment.rateGroup3.RgCycleSlips
  }

  packet SystemRes1 id 5 group 2 {
    ExamplesDeployment.systemResources.MEMORY_TOTAL
    ExamplesDeployment.systemResources.MEMORY_USED
    ExamplesDeployment.systemResources.NON_VOLATILE_TOTAL
    ExamplesDeployment.systemResources.NON_VOLATILE_FREE
  }

  packet SystemRes3 id 6 group 2 {
    ExamplesDeployment.systemResources.CPU
    ExamplesDeployment.systemResources.CPU_00
    ExamplesDeployment.systemResources.CPU_01
    ExamplesDeployment.systemResources.CPU_02
    ExamplesDeployment.systemResources.CPU_03
    ExamplesDeployment.systemResources.CPU_04
    ExamplesDeployment.systemResources.CPU_05
    ExamplesDeployment.systemResources.CPU_06
    ExamplesDeployment.systemResources.CPU_07
    ExamplesDeployment.systemResources.CPU_08
    ExamplesDeployment.systemResources.CPU_09
    ExamplesDeployment.systemResources.CPU_10
    ExamplesDeployment.systemResources.CPU_11
    ExamplesDeployment.systemResources.CPU_12
    ExamplesDeployment.systemResources.CPU_13
    ExamplesDeployment.systemResources.CPU_14
    ExamplesDeployment.systemResources.CPU_15
  }

  packet DataProducts id 20 group 3 {
    DataProducts.dpCat.CatalogDps
    DataProducts.dpCat.DpsSent

    DataProducts.dpMgr.NumSuccessfulAllocations
    DataProducts.dpMgr.NumFailedAllocations
    DataProducts.dpMgr.NumDataProducts
    DataProducts.dpMgr.NumBytes

    DataProducts.dpWriter.NumBuffersReceived
    DataProducts.dpWriter.NumBytesWritten
    DataProducts.dpWriter.NumSuccessfulWrites
    DataProducts.dpWriter.NumFailedWrites
    DataProducts.dpWriter.NumErrors

    DataProducts.dpBufferManager.TotalBuffs
    DataProducts.dpBufferManager.CurrBuffs
    DataProducts.dpBufferManager.HiBuffs
    DataProducts.dpBufferManager.NoBuffs
    DataProducts.dpBufferManager.EmptyBuffs
  }

  packet Sine id 21 group 3 {
    sine.Y
  }

  packet Version1 id 22 group 2 {
    CdhCore.version.FrameworkVersion
    CdhCore.version.ProjectVersion
  }

  packet Version_Library1 id 23 group 2 {
    CdhCore.version.LibraryVersion01
    CdhCore.version.LibraryVersion02
  }

  packet Version_Library2 id 24 group 2 {
    CdhCore.version.LibraryVersion03
    CdhCore.version.LibraryVersion04
  }

  packet Version_Library3 id 25 group 2 {
    CdhCore.version.LibraryVersion05
    CdhCore.version.LibraryVersion06
  }

  packet Version_Library4 id 26 group 2 {
    CdhCore.version.LibraryVersion07
    CdhCore.version.LibraryVersion08
  }

  packet Version_Library5 id 27 group 2 {
    CdhCore.version.LibraryVersion09
    CdhCore.version.LibraryVersion10
  }

  packet Version_Custom1 id 28 group 2 {
    CdhCore.version.CustomVersion01
  }

  packet Version_Custom2 id 29 group 2 {
    CdhCore.version.CustomVersion02
  }

  packet Version_Custom3 id 30 group 2 {
    CdhCore.version.CustomVersion03
  }

  packet Version_Custom4 id 31 group 2 {
    CdhCore.version.CustomVersion04
  }

  packet Version_Custom5 id 32 group 2 {
    CdhCore.version.CustomVersion05
  }

  packet Version_Custom6 id 33 group 2 {
    CdhCore.version.CustomVersion06
  }

  packet Version_Custom7 id 34 group 2 {
    CdhCore.version.CustomVersion07
  }

  packet Version_Custom8 id 35 group 2 {
    CdhCore.version.CustomVersion08
  }

  packet Version_Custom9 id 36 group 2 {
    CdhCore.version.CustomVersion09
  }

  packet Version_Custom10 id 37 group 2 {
    CdhCore.version.CustomVersion10
  }

} omit {
  CdhCore.cmdDisp.CommandErrors
}

module ExamplesDeployment {

  # ----------------------------------------------------------------------
  # Symbolic constants for port numbers
  # ----------------------------------------------------------------------

  enum Ports_RateGroups {
    rateGroup1
    rateGroup2
    rateGroup3
  }

  enum Ports_ComPacketQueue {
      EVENTS,
      TELEMETRY,
  };

  enum Ports_ComBufferQueue {
      FILE
  };

  topology ExamplesDeployment {

  # ----------------------------------------------------------------------
  # Subtopology imports
  # ----------------------------------------------------------------------
    import CdhCore.Subtopology
    import DataProducts.Subtopology
    import FileHandling.Subtopology

    # Project-defined
    import ManagerWorker.Subtopology
    import ExternalLibs.Subtopology

  # ----------------------------------------------------------------------
  # Instances used in the topology
  # ----------------------------------------------------------------------
    instance chronoTime
    instance rateGroup1
    instance rateGroup2
    instance rateGroup3
    instance rateGroupDriver
    instance systemResources
    instance sine
    instance timer
    instance comDriver
    instance cmdSeq
    instance comQueue
    instance commsBufferManager
    instance frameAccumulator
    instance deframer
    instance framer
    instance fprimeRouter
    instance comStub
    instance dpProducer

  # ----------------------------------------------------------------------
  # Pattern graph specifiers
  # ----------------------------------------------------------------------

    command connections instance CdhCore.cmdDisp
    event connections instance CdhCore.events
    telemetry connections instance CdhCore.tlmSend
    text event connections instance CdhCore.textLogger
    health connections instance CdhCore.$health
    param connections instance FileHandling.prmDb
    time connections instance chronoTime

  # ----------------------------------------------------------------------
  # Telemetry packets (only used when TlmPacketizer is used)
  # ----------------------------------------------------------------------

    include "ExamplesDeploymentPackets.fppi"

  # ----------------------------------------------------------------------
  # Direct graph specifiers
  # ----------------------------------------------------------------------

    connections Downlink {
        # Inputs to ComQueue (events, telemetry, file)
        CdhCore.events.PktSend -> comQueue.comPacketQueueIn[Ports_ComPacketQueue.EVENTS]
        CdhCore.tlmSend.PktSend -> comQueue.comPacketQueueIn[Ports_ComPacketQueue.TELEMETRY]
        FileHandling.fileDownlink.bufferSendOut -> comQueue.bufferQueueIn[Ports_ComBufferQueue.FILE]
        comQueue.bufferReturnOut[Ports_ComBufferQueue.FILE] -> FileHandling.fileDownlink.bufferReturn
        # ComQueue <-> Framer
        comQueue.dataOut           -> framer.dataIn
        framer.dataReturnOut -> comQueue.dataReturnIn
        # Buffer Management for Framer
        framer.bufferAllocate   -> commsBufferManager.bufferGetCallee
        framer.bufferDeallocate -> commsBufferManager.bufferSendIn
        # Framer <-> ComStub
        framer.dataOut  -> comStub.dataIn
        comStub.dataReturnOut -> framer.dataReturnIn
        # ComStatus
        comStub.comStatusOut       -> framer.comStatusIn
        framer.comStatusOut  -> comQueue.comStatusIn
    }

    connections Uplink {
        # ComStub <-> FrameAccumulator
        comStub.dataOut                -> frameAccumulator.dataIn
        frameAccumulator.dataReturnOut -> comStub.dataReturnIn
        # FrameAccumulator buffer allocations
        frameAccumulator.bufferDeallocate -> commsBufferManager.bufferSendIn
        frameAccumulator.bufferAllocate   -> commsBufferManager.bufferGetCallee
        # FrameAccumulator <-> Deframer
        frameAccumulator.dataOut -> deframer.dataIn
        deframer.dataReturnOut   -> frameAccumulator.dataReturnIn
        # Deframer <-> Router
        deframer.dataOut           -> fprimeRouter.dataIn
        fprimeRouter.dataReturnOut -> deframer.dataReturnIn
        # Router <-> Command Dispatcher
        fprimeRouter.commandOut -> CdhCore.cmdDisp.seqCmdBuff
        CdhCore.cmdDisp.seqCmdStatus -> fprimeRouter.cmdResponseIn
        # Router <-> File Uplink
        fprimeRouter.fileOut -> FileHandling.fileUplink.bufferSendIn
        FileHandling.fileUplink.bufferSendOut -> fprimeRouter.fileBufferReturnIn
    }

    connections Communications {
      # ComDriver buffer allocations
      comDriver.allocate      -> commsBufferManager.bufferGetCallee
      comDriver.deallocate    -> commsBufferManager.bufferSendIn
      
      # ComDriver <-> ComStub (Uplink)
      comDriver.$recv                     -> comStub.drvReceiveIn
      comStub.drvReceiveReturnOut -> comDriver.recvReturnIn
      
      # ComStub <-> ComDriver (Downlink)
      comStub.drvSendOut      -> comDriver.$send
      comDriver.ready         -> comStub.drvConnected
    }

    # connections FileHandling_DataProducts {
    #   # Data Products to File Downlink
    #   DataProducts.dpCat.fileOut -> FileHandling.fileDownlink.SendFile
    #   FileHandling.fileDownlink.FileComplete -> DataProducts.dpCat.fileDone
    # }

    connections RateGroups {
      # timer to drive rate group
      timer.CycleOut -> rateGroupDriver.CycleIn

      # Rate group 1
      rateGroupDriver.CycleOut[Ports_RateGroups.rateGroup1] -> rateGroup1.CycleIn
      rateGroup1.RateGroupMemberOut[0] -> cmdSeq.schedIn
      rateGroup1.RateGroupMemberOut[1] -> sine.run
      rateGroup1.RateGroupMemberOut[2] -> CdhCore.tlmSend.Run
      rateGroup1.RateGroupMemberOut[3] -> FileHandling.fileDownlink.Run
      rateGroup1.RateGroupMemberOut[4] -> comQueue.run

      # Rate group 2
      rateGroupDriver.CycleOut[Ports_RateGroups.rateGroup2] -> rateGroup2.CycleIn
      rateGroup2.RateGroupMemberOut[1] -> systemResources.run

      # Rate group 3
      rateGroupDriver.CycleOut[Ports_RateGroups.rateGroup3] -> rateGroup3.CycleIn
      rateGroup3.RateGroupMemberOut[0] -> CdhCore.$health.Run
      rateGroup3.RateGroupMemberOut[1] -> commsBufferManager.schedIn
    }

    connections CdhCore_cmdSeq {
      # Command Sequencer
      cmdSeq.comCmdOut -> CdhCore.cmdDisp.seqCmdBuff
      CdhCore.cmdDisp.seqCmdStatus -> cmdSeq.cmdResponseIn
    }

    connections FileHandling_DataProducts{
        DataProducts.dpCat.fileOut             -> FileHandling.fileDownlink.SendFile
        FileHandling.fileDownlink.FileComplete -> DataProducts.dpCat.fileDone
    }

    # DataProducts pattern connections
    connections DataProducts {
        dpProducer.productGetOut  -> DataProducts.dpMgr.productGetIn
        dpProducer.productSendOut -> DataProducts.dpMgr.productSendIn
        rateGroup1.RateGroupMemberOut[5] -> dpProducer.run
    }

    connections ExamplesDeployment {

    }

  }

}

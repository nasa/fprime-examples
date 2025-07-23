// ======================================================================
// \title  Manager.hpp
// \author mstarch
// \brief  hpp file for Manager component implementation class
// ======================================================================

#ifndef ManagerWorker_Manager_HPP
#define ManagerWorker_Manager_HPP

#include "ManagerWorker/Manager/ManagerComponentAc.hpp"

namespace ManagerWorker {

class Manager : public ManagerComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct Manager object
    Manager(const char* const compName  //!< The component name
    );

    //! Destroy Manager object
    ~Manager();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for pingIn
    //!
    //! Ping input port to show that the manager remains responsive during work
    void pingIn_handler(FwIndexType portNum,  //!< The port number
                        U32 key               //!< Value to return to pinger
                        ) override;
    //! Handler implementation for doneRecv
    //!
    //! Signal from the worker that the work is finished
    void doneRecv_handler(FwIndexType portNum,            //!< The port number
                          const Fw::Completed& completed  //!< Completion status
                          ) override;

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command START
    //!
    //! Command to start the backround work
    void START_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                          U32 cmdSeq            //!< The command sequence number
                          ) override;

    //! Handler implementation for command STOP
    //!
    //! Command to stop the background work
    void STOP_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                         U32 cmdSeq            //!< The command sequence number
                         ) override;

    //! Flag tracking if the worker is busy
    bool m_busy = false;
};

}  // namespace ManagerWorker

#endif

// ======================================================================
// \title  Worker.hpp
// \author mstarch
// \brief  hpp file for Worker component implementation class
// ======================================================================
#ifndef ManagerWorker_Worker_HPP
#define ManagerWorker_Worker_HPP
#include <atomic>
#include "ManagerWorker/Worker/WorkerComponentAc.hpp"

namespace ManagerWorker {

class Worker : public WorkerComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct Worker object
    Worker(const char* const compName  //!< The component name
    );

    //! Destroy Worker object
    ~Worker();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for cancelWork
    //!
    //! Signal to cancel the work
    void cancelWork_handler(FwIndexType portNum  //!< The port number
                            ) override;

    //! Handler implementation for startWork
    //!
    //! Signal to start the work
    void startWork_handler(FwIndexType portNum  //!< The port number
                           ) override;

    std::atomic<bool> m_cancel; //!< Flag to cancel the work
};

}  // namespace ManagerWorker

#endif

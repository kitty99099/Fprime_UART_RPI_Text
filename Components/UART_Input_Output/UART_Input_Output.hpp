// ======================================================================
// \title  UART_Input_Output.hpp
// \author tt
// \brief  hpp file for UART_Input_Output component implementation class
// ======================================================================

#ifndef Components_UART_Input_Output_HPP
#define Components_UART_Input_Output_HPP

#include "Components/UART_Input_Output/UART_Input_OutputComponentAc.hpp"
#include <Os/Mutex.hpp>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

namespace Components {

  class UART_Input_Output :
    public UART_Input_OutputComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Component construction and destruction
      // ----------------------------------------------------------------------

      //! Construct UART_Input_Output object
      UART_Input_Output(
          const char* const compName //!< The component name
      );

      //! Destroy UART_Input_Output object
      ~UART_Input_Output();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for run
      //!
      //! Port receiving calls from the rate group
      void run_handler(
          NATIVE_INT_TYPE portNum, //!< The port number
          NATIVE_UINT_TYPE context //!< The call order
      ) override;

      //! Handler implementation for UartRead
      //!
      //! Input port for receiving UART data
      void UartRead_handler(
          NATIVE_INT_TYPE portNum, //!< The port number
          Fw::Buffer& recvBuffer,
          const Drv::RecvStatus& recvStatus
      ) override;

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for commands
      // ----------------------------------------------------------------------

      //! Handler implementation for command SAY_HELLO
      //!
      //! Command to issue output_greeting with maximum length of 20 characters
      void SAY_HELLO_cmdHandler(
          FwOpcodeType opCode, //!< The opcode
          U32 cmdSeq, //!< The command sequence number
          const Fw::CmdStringArg& output_greeting
      ) override;

      Os::Mutex lock; //! Protects our data from thread race conditions
      U32 inputCount;
      U32 outputCount;
      Fw::LogStringArg Leaved_Text;
      U32 frequency;
      U32 m_uartWriteBytes;
      U32 m_uartReadBytes;
      Fw::String m_lastUartMsg;

      void parameterUpdated(FwPrmIdType id
      ) override;

  };

}

#endif

// ======================================================================
// \title  UART_Input_Output.cpp
// \author tt
// \brief  cpp file for UART_Input_Output component implementation class
// ======================================================================

#include "Components/UART_Input_Output/UART_Input_Output.hpp"
#include "FpConfig.hpp"

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  UART_Input_Output ::
    UART_Input_Output(const char* const compName) :
      UART_Input_OutputComponentBase(compName),
      inputCount(0),
      outputCount(0),
      frequency(0),
      m_uartWriteBytes(0),
      m_uartReadBytes(0)
  {

  }

  UART_Input_Output ::
    ~UART_Input_Output()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void UART_Input_Output ::
    run_handler(
        NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    //int serial_port = open("/dev/serial0", O_RDWR);This!!!

    //struct termios tty;
    //tcgetattr(serial_port, &tty);

    //cfsetospeed(&tty, B9600);
    //cfsetispeed(&tty, B9600);

    //tty.c_cflag &= ~PARENB; // No parity bit
    //tty.c_cflag &= ~CSTOPB; // 1 stop bit
    //tty.c_cflag &= ~CSIZE;
    //tty.c_cflag |= CS8; // 8 bits per byte

    //tcsetattr(serial_port, TCSANOW, &tty);

    //Fw::LogStringArg *msg = &Leaved_Text;
    //write(serial_port, msg, strlen(msg->toChar()));This!!!

    //const char *msg = "Hello World\n";Test!!!
    //write(serial_port, msg, strlen(msg));
    //std::cout << "Sent: " << msg << std::endl;Test!!!

    //close(serial_port);End!!!
  }

  void UART_Input_Output ::
    UartRead_handler(
        NATIVE_INT_TYPE portNum,
        Fw::Buffer& recvBuffer,
        const Drv::RecvStatus& recvStatus
    )
  {
    if (Drv::RecvStatus::RECV_OK == recvStatus.e) {
          // convert incoming data to string. If it is not printable, set chara>
          char uMsg[recvBuffer.getSize() + 1];

          std::cout << "recvBuffer: " << recvBuffer.getSize() << std::endl;
          std::cout << "recvBuffer: " << recvBuffer.getData() << std::endl;
          
          char *bPtr = reinterpret_cast<char *>(recvBuffer.getData());

          for (NATIVE_UINT_TYPE byte = 0; byte < recvBuffer.getSize(); byte++) {
            uMsg[byte] = isalpha(bPtr[byte]) ? bPtr[byte] : '*';
          }
          uMsg[sizeof(uMsg) - 1] = 0;

          Fw::LogStringArg evrMsg(uMsg);
          this->log_ACTIVITY_HI_RECEIVED_GREETING(evrMsg);
          this->m_uartReadBytes += recvBuffer.getSize();
          this->tlmWrite_RD_UartRecvBytes(this->m_uartReadBytes);
    }
    // return buffer to buffer manager
    this->UartBuffers_out(0, recvBuffer);
  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void UART_Input_Output ::
    SAY_HELLO_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq,
        const Fw::CmdStringArg& output_greeting
    )
  {
    Fw::Buffer txt;
    txt.setSize(output_greeting.length());
    txt.setData(reinterpret_cast<U8*>(const_cast<char*>(output_greeting.toChar())));
    Drv::SendStatus status = this->UartWrite_out(0, txt);
    if (Drv::SendStatus::SEND_OK == status.e) {
      this->m_uartWriteBytes += output_greeting.length();
      this->tlmWrite_RD_UartSentBytes(this->m_uartWriteBytes);
      Fw::LogStringArg Leaved_Text(output_greeting.toChar());
      this->log_ACTIVITY_HI_LEAVED_GREETING(Leaved_Text);
    }

    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

  void UART_Input_Output ::
    parameterUpdated(FwPrmIdType id)
  {
    Fw::ParamValid isValid;
    frequency = this->paramGet_FREQUENCY_GREETING(isValid);
    FW_ASSERT(isValid == Fw::ParamValid::VALID, isValid);

    if (PARAMID_FREQUENCY_GREETING == id){
      this->log_ACTIVITY_HI_FREQUENCY_SETTING(frequency);
    }
  }
}

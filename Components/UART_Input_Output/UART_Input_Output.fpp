module Components {
    @ No description
    active component UART_Input_Output {

        # One async command/port is required for active components
        # This should be overridden by the developers with a useful command/port
        @ Command to issue output_greeting with maximum length of 20 characters
        async command SAY_HELLO(output_greeting: string size 20)

        @ Parameter to set the frequency of output_greeting
        param FREQUENCY_GREETING: U32

        @ Event to show the output_greeting
        event LEAVED_GREETING(output_greeting: string size 20)\
        severity activity high\
        format "Leaved: {}"

        @ Event to show the setting of frequency
        event FREQUENCY_SETTING(frequency: U32)\
        severity activity high\
        format "The frequency is set to {}"

        @ Event to show the input_greeting
        event RECEIVED_GREETING(input_greeting: string size 20)\
        severity activity high\
        format "Received: {}"

        @ Port receiving calls from the rate group
        sync input port run: Svc.Sched

        @ Port sending calls to the GPIO driver
        output port gpioSet: Drv.GpioWrite

        @ Input port for receiving UART data
        async input port UartRead: Drv.ByteStreamRecv

        @ Output Port for writing UART data
        output port UartWrite: Drv.ByteStreamSend

        @ Output port for sending UART buffers to use for reading
        output port UartBuffers: Fw.BufferSend

        @ Number of bytes received on the UART
        telemetry RD_UartRecvBytes: U32

        @ Number of bytes sent on the UART
        telemetry RD_UartSentBytes: U32
        ##############################################################################
        #### Uncomment the following examples to start customizing your component ####
        ##############################################################################

        # @ Example async command
        # async command COMMAND_NAME(param_name: U32)

        # @ Example telemetry counter
        # telemetry ExampleCounter: U64

        # @ Example event
        # event ExampleStateEvent(example_state: Fw.On) severity activity high id 0 format "State set to {}"

        # @ Example port: receiving calls from the rate group
        # sync input port run: Svc.Sched

        # @ Example parameter
        # param PARAMETER_NAME: U32

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Port for sending command registrations
        command reg port cmdRegOut

        @ Port for receiving commands
        command recv port cmdIn

        @ Port for sending command responses
        command resp port cmdResponseOut

        @ Port for sending textual representation of events
        text event port logTextOut

        @ Port for sending events to downlink
        event port logOut

        @ Port for sending telemetry channels to downlink
        telemetry port tlmOut

        @ Port to return the value of a parameter
        param get port prmGetOut

        @Port to set the value of a parameter
        param set port prmSetOut

    }
}

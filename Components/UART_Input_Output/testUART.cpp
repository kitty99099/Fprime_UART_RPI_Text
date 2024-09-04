#include <iostream>
#include <fcntl.h> // For file controls
#include <unistd.h> // For read/write functions
#include <termios.h> // For serial port controls
#include <string.h>

int main() {
    int serial_port = open("/dev/serial0", O_RDWR);

    struct termios tty;
    tcgetattr(serial_port, &tty);

    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);

    tty.c_cflag &= ~PARENB; // No parity bit
    tty.c_cflag &= ~CSTOPB; // 1 stop bit
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8; // 8 bits per byte

    tcsetattr(serial_port, TCSANOW, &tty);

    const char *msg = "Hello World\n";

    while (true){
        write(serial_port, msg, strlen(msg));
        std::cout << "Sent: " << msg << std::endl;
        sleep(1);
    }

    close(serial_port);
}

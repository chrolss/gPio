#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

#ifndef UART_H_
#define UART_H_

class uart{
public:
	uart();
	int initialize();
	int sendMsg(char *_msg);
	int readMsg();
	int contRead();
	int joystickRead();
	int closeUART();

private:
	int fd;


};

#endif

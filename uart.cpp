#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include "uart.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>


uart::uart(){
	initialize();
}

int uart::initialize(){

	struct termios options;
	int status;
	this->fd = open("/dev/ttyS0",O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK);
	if (fd == -1) {
		perror("open_port: Unable to open /dev/ttyS0 - ");
		return -1;
	}
	fcntl(fd, F_SETFL, O_RDWR);
	tcgetattr (fd, &options) ;

	cfmakeraw   (&options) ;
	cfsetispeed (&options, B9600) ;
	cfsetospeed (&options, B9600) ;

	options.c_cflag |= (CLOCAL | CREAD) ;
	options.c_cflag &= ~PARENB ;
	options.c_cflag &= ~CSTOPB ;
	options.c_cflag &= ~CSIZE ;
	options.c_cflag |= CS8 ;
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG) ;
	options.c_oflag &= ~OPOST ;

	options.c_cc [VMIN]  =   0 ;
	options.c_cc [VTIME] = 100 ;	// Ten seconds (100 deciseconds)

	tcsetattr (fd, TCSANOW | TCSAFLUSH, &options) ;

	ioctl (fd, TIOCMGET, &status);

	status |= TIOCM_DTR ;
	status |= TIOCM_RTS ;

	ioctl (fd, TIOCMSET, &status);

	usleep (10000) ;	// 10mS
	printf("/dev/ttyS0 opened\n");
	return 1;
}

int uart::sendMsg(char *_msg){
	  // Turn off blocking for reads, use (fd, F_SETFL, FNDELAY) if you want that
	  fcntl(fd, F_SETFL, 0);

	  // Write to the port
	  char *msg = "tja";
	  int n = write(fd, msg, 4);	// change the 4 to a general buffLength
	  if (n < 0) {
	    perror("Write failed - ");
	    return -1;
	  }
	  return 1;
}

int uart::readMsg(){
	// Read up to 255 characters from the port if they are there
	// NEEDS CLEANING
	char buf[256];
	int n = read(this->fd, (void*)buf, 255);
	//int n = read(this->fd, buf, sizeof(buf));
	if (n < 0) {
		perror("Read failed - ");
	return -1;
	}
	else if (n == 0){
		printf("No data on port\n");
		return -1;
	}
	else {
		buf[n] = '\0';
		printf("%i bytes read : %d \n", n, (int)buf & 0xFF);
		return 1;
	}
}

int uart::contRead(){
	char buf[256];
	int n = read(this->fd, (void*)buf, 255);
	for (int j = 0; j<50; j++){
		//int n = read(this->fd, buf, sizeof(buf));
		if (n < 0) {
			perror("Read failed - ");
		}
		else if (n == 0){
			printf("No data on port\n");
		}
		else {
			buf[n] = '\0';
			printf("%i bytes read : %d \n", n, (int)buf[0] & 0xFF);
		}
		n = read(this->fd, (void*)buf, 255);
		//usleep(1000);
	}
	return 1;

}

int uart::joystickRead(){
	char buf[256];
	char sec[256];
	int n = read(this->fd, (void*)buf, 1);
	int m = read(this->fd, (void*)sec, 1);
	int compVal;
   // read one larger buffer, find start byte and navigate accordingly
	for (int j = 0; j<50; j++){
		//int n = read(this->fd, buf, sizeof(buf));
		if (n < 0) {
			perror("Read failed - ");
		}
		else if (n == 0){
			printf("No data on port\n");
		}
		else {
			buf[n] = '\0';
			compVal = (int)buf[0] & 0xFF;
			if (compVal = 4){
				printf("compval: %d, val: %d \n", compVal, (int)sec[0] & 0xFF);
			}
		}
		n = read(this->fd, (void*)buf, 1);
		m = read(this->fd, (void*)sec, 1);
		//usleep(1000);
	}
	return 1;
}

int uart::closeUART(){
	close(this->fd);
	printf("UART com closed\n");
	return 1;
}

/*
int main(int argc, char ** argv) {
  int fd;
  // Open the Port. We want read/write, no "controlling tty" status, and open it no matter what state DCD is in
  fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1) {
    perror("open_port: Unable to open /dev/ttyS0 - ");
    return(-1);
  }

  // Turn off blocking for reads, use (fd, F_SETFL, FNDELAY) if you want that
  fcntl(fd, F_SETFL, 0);

  // Write to the port
  char *msg = "tja";
  int n = write(fd, msg, 4);	// change the 4 to a general buffLength
  if (n < 0) {
    perror("Write failed - ");
    return -1;
  }

  // Read up to 255 characters from the port if they are there
  char buf[256];
  n = read(fd, (void*)buf, 255);
  if (n < 0) {
    perror("Read failed - ");
    return -1;
  } else if (n == 0) printf("No data on port\n");
  else {
    buf[n] = '\0';
    printf("%i bytes read : %s", n, buf);
  }

  // Don't forget to clean up
  close(fd);
  return 0;
}
*/


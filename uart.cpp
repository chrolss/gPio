#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

uart::uart(){
	initialize();
}

int uart::initialize(){
	this->fd = open("/dev/ttyS0",O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1) {
		perror("open_port: Unable to open /dev/ttyS0 - ");
		return -1;
	}
	printf("/dev/ttyS0 opened");
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

std::string uart::readMsg(){
	// Read up to 255 characters from the port if they are there
	// NEEDS CLEANING
	char buf[256];
	int n = read(this->fd, (void*)buf, 255);
	if (n < 0) {
		perror("Read failed - ");
	return "null";
	}
	else if (n == 0){
		printf("No data on port\n");
		return "null";
	}
	else {
		buf[n] = '\0';
		printf("%i bytes read : %s", n, buf);
		return "msg";
	}
}

int uart::closeUART(){
	close(this->fd);
	printf("UART com closed");
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


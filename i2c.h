#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#ifndef I2C_H_
#define I2C_H_

class i2c{
public:
	i2c(std::string _device);
	int initialize();
	int read(int _devAdress, char _register);
        Int write(int _devAdress, char _register);
	int closei2c();
private:
	std::string devName;
        Char txBuffer[32]; //transmit buffer 
        Char rxBuffer[32]; //receiver buffer
        Int i2cHandle;
        Int opResult; //operation result handle
        Int tenBitAddress = 0;
};

#endif

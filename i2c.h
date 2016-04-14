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
	int read(char _register);
        Int write(char _register);
	int closei2c();
private:
	std::string devName;
        char txBuffer[32]; //transmit buffer 
        char rxBuffer[32]; //receiver buffer
        int i2cHandle;
        int opResult; //operation result handle
        int tenBitAddress = 0;
        char devAddress;
};

#endif

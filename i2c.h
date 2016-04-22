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
	i2c(int _devAddress);
	int initialize();
	int readReg(char _register);
	int writeReg(char _register, int _bit);
	int closei2c();
private:
	char txBuffer[32]; //transmit buffer
	char rxBuffer[32]; //receiver buffer
	int i2cHandle;
	int opResult; //operation result handle
	int tenBitAddress;
	char devAddress;
};

#endif

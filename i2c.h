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
	int readData();
	int writeData();
	int closei2c();
private:
	std::string devName;
};

#endif

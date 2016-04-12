#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "i2c.h"

#ifndef HATCONTROL_H_
#define HATCONTROL_H_

class hatControl{
public:
	void initialize();
	void setQuadPWM(double _val1, double _val2, double _val3, double _val4);
	void cleanUp();
private:
	uint8_t devAdress = 0x40;
};

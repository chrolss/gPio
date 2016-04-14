#include "i2c.h"

i2c::i2c(int _devAddress){
	this->devAddress = _devAddress; //test register, not real. need to add devAdress in private field of i2c.h
	this->i2cHandle = open("/dev/i2c-1", O_RDWR);
	memset(this->rxBuffer, 0, sizeof(this->rxBuffer));
	memset(this->txBuffer, 0, sizeof(this->txBuffer));
	this->tenBitAddress = 0;
	this->opResult = ioctl(this->i2cHandle, I2C_TENBIT, tenBitAddress); //setting the device address as 8-bit
	this->opResult = ioctl(this->i2cHandle, I2C_SLAVE, devAddress); //tell the i2c periheral which address to communicate with
}

int i2c::readReg(char _register){
	this->txBuffer[0] = _register;
    this->opResult = write(this->i2cHandle, txBuffer, 1);
    if (opResult != 1){
    	printf("No ack bit");
    }
    opResult = read(this->i2cHandle, this->rxBuffer, 1);
    return (int)txBuffer[0];
}

int i2c::writeReg(char _register){
	this->txBuffer[0] = _register;
	this->opResult = write(this->i2cHandle, txBuffer, 1);
	if (opResult != 1){
		printf("No ack bit!\n");
		return -1;
	}
	return opResult;
	}


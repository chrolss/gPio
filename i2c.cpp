#include "i2c.h"

i2c::i2c(std::string _device){
	if (_device == "adxl"){
		this->devName = "adxl";
                this->devAddress = 0x43; //test register, not real. need to add devAdress in private field of i2c.h
	}
        this->i2cHandle = open("/dev/i2c-1", O_RWDR);
        memset(this->rxBuffer, 0, sizeOf(this->rxBuffer));
        memset(this->txBuffer, 0, sizeOf(this->txBuffer));
        this->opResult = ioctl(this->i2cHandle, I2C_TENBIT, this->tenBitAddress); //setting the device address as 8-bit
        this->opResult = ioctl(this->i2cHandle, I2C_SLAVE, this->devAdress); //tell the i2c periheral which address to communicate with       
}

int i2c::read(char _register){
       this->txBuffer[0] = _register;
       this->opResult = write(this->i2cHandle, txBuffer, 1);
       if (opResult != 1){
            printf("No ack bit");
       }
       opResult = read(i2cHandle, this->rxBuffer, 1);
       return (int)txBuffer[0];       
}

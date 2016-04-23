#include "pwm.h"

pwm::pwm(){
	initialize();
}
void pwm::initialize(){
	this->i2cHandle = open("/dev/i2c-1", O_RDWR);
	memset(this->rxBuffer, 0, sizeof(this->rxBuffer));
	memset(this->txBuffer, 0, sizeof(this->txBuffer));
	this->opRes = ioctl(this->i2cHandle, I2C_TENBIT, 0); //setting the device address as 8-bit
	this->opRes = ioctl(this->i2cHandle, I2C_SLAVE, 0x40); //tell the i2c periheral which address to communicate with

	//put some code here that sets the ON/OFF_L/H depending on
	//pin number
}

void pwm::setDutyCycle(double _duty){
	double val = 4096.0*(_duty/100);	//duty percentage to 4096 bit value
	txBuffer[0] = LED0_ON_H;
	txBuffer[1] = 0;
	opRes = write(this->i2cHandle, txBuffer, 2);
	txBuffer[0] = LED0_ON_L;
	txBuffer[1] = 0;
	opRes = write(this->i2cHandle, txBuffer, 2);
	txBuffer[0] = LED0_OFF_H;
	txBuffer[1] = (int)val & 0xFF;
	opRes = write(this->i2cHandle, txBuffer, 2);
	txBuffer[0] = LED0_OFF_L;
	txBuffer[1] = (int)val >> 8;
	opRes = write(this->i2cHandle, txBuffer, 2);
}

void pwm::setFrequency(int _freq){
	double val = 25000000.0/4096.0;
	double preVal = val/(double)_freq;
	preVal = preVal - 1;
	int setVal = floor(preVal + 0.5);
	txBuffer[0] = 0xFE;
	txBuffer[1] = setVal;
	opRes = write(this->i2cHandle, txBuffer, 2);
	if (opRes != 2){
		printf("Error when writing frequency\n");
	}

}

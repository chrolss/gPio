/*
 * main.cpp
 *
 *  Created on: Mar 30, 2016
 *      Author: christian
 *      kom igen
 */

#include "gpio.h"
#include "unistd.h"
#include <stdio.h>
#include "i2c.h"
#include <iostream>

void testGPIO(){
		gpio* testPin = new gpio("21", "out");
		printf("Turning on pin nr.21\n");
		testPin->setValue(1);
		usleep(5000000); //wait for 5 seconds
		printf("Turning off pin nr.21\n");
		testPin->setValue(0);
		testPin->closePin();
}

void testFromInternet(){
	char rxBuffer[32];  // receive buffer
	  char txBuffer[32];  // transmit buffer
	  int gyroAddress = 0x68; // gyro device address
	  int xlAddress = 0x53;   // accelerometer device address
	  int tenBitAddress = 0;  // is the device's address 10-bit? Usually not.
	  int opResult = 0;   // for error checking of operations

	  // Create a file descriptor for the I2C bus
	  int i2cHandle = open("/dev/i2c-1", O_RDWR);

	  // Tell the I2C peripheral that the device address is (or isn't) a 10-bit
	  //   value. Most probably won't be.
	  opResult = ioctl(i2cHandle, I2C_TENBIT, tenBitAddress);

	  // Tell the I2C peripheral what the address of the device is. We're going to
	  //   start out by talking to the gyro.
	  opResult = ioctl(i2cHandle, I2C_SLAVE, gyroAddress);

	  // Clear our buffers
	  memset(rxBuffer, 0, sizeof(rxBuffer));
	  memset(txBuffer, 0, sizeof(txBuffer));

	  // The easiest way to access I2C devices is through the read/write
	  //   commands. We're going to ask the gyro to read back its "WHO_AM_I"
	  //   register, which contains the I2C address. The process is easy- write the
	  //   desired address, the execute a read command.
	  txBuffer[0] = 0x75; // This is the address we want to read from.
	  opResult = write(i2cHandle, txBuffer, 1);
	  if (opResult != 1) printf("No ACK bit!\n");
	  opResult = read(i2cHandle, rxBuffer, 1);
	  printf("Part ID: %d\n", (int)rxBuffer[0]); // should print 105
}

void testGyro(){
	char rxBuffer[32];  // receive buffer
	  char txBuffer[32];  // transmit buffer
	  int gyroAddress = 0x68; // gyro device address
	  int xlAddress = 0x53;   // accelerometer device address
	  int tenBitAddress = 0;  // is the device's address 10-bit? Usually not.
	  int opResult = 0;   // for error checking of operations

	  // Create a file descriptor for the I2C bus
	  int i2cHandle = open("/dev/i2c-1", O_RDWR);

	  // Tell the I2C peripheral that the device address is (or isn't) a 10-bit
	  //   value. Most probably won't be.
	  opResult = ioctl(i2cHandle, I2C_TENBIT, tenBitAddress);

	  // Tell the I2C peripheral what the address of the device is. We're going to
	  //   start out by talking to the gyro.
	  opResult = ioctl(i2cHandle, I2C_SLAVE, gyroAddress);

	  // Clear our buffers
	  memset(rxBuffer, 0, sizeof(rxBuffer));
	  memset(txBuffer, 0, sizeof(txBuffer));

	  // The easiest way to access I2C devices is through the read/write
	  //   commands. We're going to ask the gyro to read back its "WHO_AM_I"
	  //   register, which contains the I2C address. The process is easy- write the
	  //   desired address, the execute a read command.
	  txBuffer[0] = 0x6B;
	  opResult = write(i2cHandle, txBuffer, 1); //wake it up
	  sleep(1);

	  // TO DO - WRITE ALL SETUP CODE FROM ARDUINO PAGE TO GET STABLE READINGS
	  int count = 0;
	  while (count < 100){
		  txBuffer[0] = 0x43; // This is the address we want to read from.
		  opResult = write(i2cHandle, txBuffer, 1);
		  if (opResult != 1) printf("No ACK bit!\n");
		  int L = read(i2cHandle, rxBuffer, 1);
		  L = rxBuffer[0];
		  txBuffer[0] = 0x44; // This is the address we want to read from.
		  opResult = write(i2cHandle, txBuffer, 1);
		  if (opResult != 1) printf("No ACK bit!\n");
		  int H = read(i2cHandle, rxBuffer, 1);
		  H = rxBuffer[0];
		  for (int i = 0; i<8; i++){
			  printf("%d",rxBuffer[i]);
		  }
		  printf("\n");
		  /*
		  std::cout << H << " och " << L << std::endl;
		  int16_t tesRes = ((H<<8)+L);
		  std::cout << ((tesRes+12412)/340) << std::endl;
		  */
		  count = count + 1;
		  sleep(1);
	  }
}

void testi2c(){
	i2c* testDev = new i2c(0x68);
	int opRes = testDev->writeReg(0x6B, 1);
	int testRes = testDev->readReg(0x75); //read "who am I?"
	printf("I am %d\n", testRes);

	//read raw sensor values
	int rawResL = testDev->readReg(0x43);
	printf("least gyro %d\n", rawResL);
	int rawResM = testDev->readReg(0x44);
	printf("most gyro %d\n", rawResM);
}

int main(){
	//testGPIO();
	//testi2c();
	//testFromInternet();
	testGyro();
}



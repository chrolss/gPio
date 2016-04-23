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
#include "mpu9150.h"
#include <iostream>
#include "pwm.h"

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
	  txBuffer[1] = 1;
	  opResult = write(i2cHandle, txBuffer, 2); //wake it up
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
	int testRes = testDev->writeReg(0x6B, 1, 2);
	testRes = testDev->writeReg(0x24, 0x40, 2); //Wait for Data at Slave0
	testRes = testDev->writeReg(0x25, 0x8C, 2); //Set i2c address at slave0 at 0x0C
	testRes = testDev->writeReg(0x26, 0x02, 2); //Set where reading at slave 0 starts
	testRes = testDev->writeReg(0x27, 0x88, 2); //set offset at start reading and enable
	testRes = testDev->writeReg(0x28, 0x0C, 2); //set i2c address at slv1 at 0x0C
	testRes = testDev->writeReg(0x29, 0x0A, 2); //Set where reading at slave 1 starts
	testRes = testDev->writeReg(0x2A, 0x81, 2); //Enable at set length to 1
	testRes = testDev->writeReg(0x64, 0x01, 2); //overvride register
	testRes = testDev->writeReg(0x67, 0x03, 2); //set delay rate
	testRes = testDev->writeReg(0x01, 0x80, 2);

	testRes = testDev->writeReg(0x34, 0x04, 2); //set i2c slv4 delay
	testRes = testDev->writeReg(0x64, 0x00, 2); //override register
	testRes = testDev->writeReg(0x6A, 0x00, 2); //clear usr setting
	testRes = testDev->writeReg(0x64, 0x01, 2); //override register
	testRes = testDev->writeReg(0x6A, 0x20, 2); //enable master i2c mode
	testRes = testDev->writeReg(0x34, 0x13, 2); //disable slv4

	testRes = testDev->readReg(0x75); //read "who am I?"
	printf("I am %d\n", testRes);

	//read raw sensor values
	for (int i = 0; i<10; i++){
		int accRead = testDev->readAcc();
		int gyroRead = testDev->readGyro();
		printf("X-acc: %d , X-gyro : %d\n", accRead, gyroRead);
		//int rawResL = testDev->readReg(0x43);
		//printf("least gyro %d\n", rawResL);
		//int rawResM = testDev->readReg(0x44);
		//printf("most gyro %d\n", rawResM);
		sleep(1);
	}
}

void testMPU(){
	mpu9150* mpu = new mpu9150();
	double testArr [3];
	for (int i = 0;i<200;i++){
		mpu->getAccelerations(testArr);
		//printf("X: %f, Y: %f, Z: %f\n", testArr[0], testArr[1], testArr[2]);
		printf("Pitch: %f, Roll: %f\n", mpu->getPitch(), mpu->getRoll());
		usleep(100000);
	}
}

void testPWM(){
	pwm* Pewm = new pwm();
	double frekk;
	printf("Set frequency: ");
	std::cin >> frekk;
	Pewm->setFrequency(frekk);
	Pewm->setDutyCycle(0.0);
	printf("set it to 0.0\n");
	usleep(100000);
	double answer;
	for (int k = 0;k<10; k++){
		printf("Give pwm: ");
		std::cin >> answer;
		Pewm->setDutyCycle(answer);
		printf("\n set it to %f\n", answer);
	}
}

void playGround(){
	pwm* Pewm = new pwm();
	double frekk;
	printf("Set frequency: ");
	std::cin >> frekk;
	Pewm->setFrequency(frekk);
	Pewm->setDutyCycle(0.0);
	printf("set it to 0.0\n");
	usleep(100000);
	mpu9150* mpu = new mpu9150();
	double testArr [3];
	double pitch;
	double duty;
	for (int i = 0;i<20000;i++){
		mpu->getAccelerations(testArr);
		pitch = mpu->getPitch();
		duty = 5.0/90*pitch + 8;
		Pewm->setDutyCycle(duty);
		usleep(1000);
	}
}

int main(){
	//testGPIO();
	//testi2c();
	//testFromInternet();
	//testGyro();
	//testMPU();
	//testPWM();
	playGround();
}

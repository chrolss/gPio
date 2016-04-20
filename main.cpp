/*
 * main.cpp
 *
 *  Created on: Mar 30, 2016
 *      Author: christian
 *      kom igen
 */
// funkar det?
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


void testi2c(){
	i2c* testDev = new i2c(0x77);
	int testRes = testDev->readReg(0x00);
	std::cout << testRes << std::endl;
}

int main(){
	//testGPIO();
	testi2c();
}



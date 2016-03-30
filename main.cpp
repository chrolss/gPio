/*
 * main.cpp
 *
 *  Created on: Mar 30, 2016
 *      Author: christian
 */

#include "gpio.h"
#include "unistd.h"

int main(){
	gpio testPin = new gpio("4", "out");
	printf("Turning on pin nr.4");
	testPin.setValue(1);
	usleep(5000000); //wait for 5 seconds
	printf("Turning off pin nr.4");
	testPin.setValue(0);
	testPin.closePin();
}



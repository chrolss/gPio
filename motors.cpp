#include "motors.h"

motors::motors(){
	initialize();
}

int motors::initialize(){
	this->pwmHandle = new pwm();
	pwmHandle->setFrequency(1000000);
	usleep(10000); // give time to set frequency
	pwmHandle->setQuadDutyCycle(stopDuty);
	usleep(10000); // give time to start all ESC
	printf("Engines started\n");
	return 1;
}

int motors::closeMotors(){
	stopMotors();
	printf("Engines stopped\n");
	return 1;
}

int motors::setSpeed(double &_speeds){
	// &_speeds = [RF, RR, LR, LF]
	// TODO: SPEEDS ARE CURRENTLY GIVEN IN PWM DUTYCYCLE LEVELS, E.G. 20-49
	// CHANGE TO 0 - 100 MAPPING
	pwmHandle->setQuadDutyCycle(_speeds);
	return 1;
}

int motors::stopMotors(){
	pwmHandle->setQuadDutyCycle(stopDuty);
	return 1;
}

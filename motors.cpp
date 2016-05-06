#include "motors.h"

motors::motors(){
	initialize();
}

int motors::initialize(){
	this->pwmHandle = new pwm();
	pwmHandle->setFrequency(200000000);
	usleep(1000000); // give time to set frequency
	pwmHandle->setQuadDutyCycle(stopDuty);
	usleep(1000000); // give time to start all ESC
	printf("Engines started\n");
	this->stopDuty[0] = 20.0;
	this->stopDuty[1] = 20.0;
	this->stopDuty[2] = 20.0;
	this->stopDuty[3] = 20.0;
	return 1;
}

int motors::closeMotors(){
	stopMotors();
	printf("Engines stopped\n");
	return 1;
}

int motors::setSpeed(double* _speeds){
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

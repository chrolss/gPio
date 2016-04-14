#include "pwm.h"

pwm::pwm(int _pin){
	initialize(_pin);
}
void pwm::initialize(int _pin){
	this->pinNr = _pin;
	//put some code here that sets the ON/OFF_L/H depending on
	//pin number
}

void pwm::setDutyCycle(double _val){
	double duty = 4096.0/_val;
}

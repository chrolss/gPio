#include <iostream>
#include "pwm.h"

class motors{
public:
	motors();
	int setSpeed(double &_speeds);
	int stopMotors();
	int closeMotors();
private:
	int initialize();
	pwm* pwmHandle;
	double stopDuty = {0.0,0.0,0.0,0.0};
};

#include "i2c.h"

i2c::i2c(std::string _device){
	if (_device == "adxl"){
		this->devName = "adxl";
	}
}

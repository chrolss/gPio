// Created by Christian 2016-03-30

#include <fstream>
#include <iostream>
#include <sstream>

#include "gpio.h"

gpio::gpio(std::string _pin, string _dir){
	//always initialize with 0 value
	this->pinName = _pin;
	this->value = 0;
	this->direction = _dir;
	exportPin();
	setValue(value);
	setDirection(_dir);
};

std::string gpio::getPinName(){
	return this->pinName;
}

int gpio::exportPin(){
	string export_str = "/sys/class/gpio/export";
	ofstream exportgpio(export_str.c_str()); // Open "export" file. Convert C++ string to C string. Required for all Linux pathnames
	if (exportgpio < 0){
		cout << " OPERATION FAILED: Unable to export GPIO"<< this->pinName <<" ."<< endl;
		return -1;
	}

	exportgpio << this->pinName ; //write GPIO number to export
	exportgpio.close(); //close export file
	return 1;
}

int gpio::unexportPin(){
    string unexport_str = "/sys/class/gpio/unexport";
    ofstream unexportgpio(unexport_str.c_str()); //Open unexport file
    if (unexportgpio < 0){
        cout << " OPERATION FAILED: Unable to unexport GPIO"<< this->pinName <<" ."<< endl;
        return -1;
    }

    unexportgpio << this->pinName ; //write GPIO number to unexport
    unexportgpio.close(); //close unexport file
    return 1;
}

int gpio::setValue(int _val){
	string setval_str = "/sys/class/gpio/gpio" + this->pinName + "/value";
	ofstream setvalgpio(setval_str.c_str()); // open value file for gpio
	if (setvalgpio < 0){
		std::cout << " OPERATION FAILED: Unable to set the value of GPIO"<< this->pinName <<" ."<< std::endl;
		return -1;
	}

	setvalgpio << _val ;//write value to value file
	setvalgpio.close();// close value file
	return 0;
}

int gpio::setDirection(std::string _dir){
    string setdir_str ="/sys/class/gpio/gpio" + this->pinName + "/direction";
    ofstream setdirgpio(setdir_str.c_str()); // open direction file for gpio
	if (setdirgpio < 0){
		cout << " OPERATION FAILED: Unable to set direction of GPIO"<< this->pinName <<" ."<< endl;
		return -1;
	}

	setdirgpio << _dir; //write direction to direction file
	setdirgpio.close(); // close direction file
	return 0;
}

std::string gpio::getDirection(){
	return this->direction;
}

int gpio::getValue(){
	return this->value;
}

int gpio::closePin(){
	setValue(0);
	unexportPin();
	return 1;
}

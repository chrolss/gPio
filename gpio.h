//Created by Christian 2016-03-30

#ifndef GPIO_H_
#define GPIO_H_
#include <string>

using namespace std;

class gpio{
public:
	gpio(string _pin, int _dir);	//constructor
	int setValue(int _val);
	int getValue();
	int setDirection(int _dir);
	int getDirection();
	string getPinName();
	int closePin();
private:
	string pinName;
	int value;
	int direction;
	int exportPin();
	int unexportPin();
};

#endif

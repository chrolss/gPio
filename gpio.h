//Created by Christian 2016-03-30

#ifndef GPIO_H_
#define GPIO_H_
#include <string>

using namespace std;

class gpio{
public:
	gpio(string _pin);	//constructor
	int setValue(int _val);
	int getValue();
	int setDirection(int _dir);
	int getDirection(int _dir);
	string getPinName();
private:
	string pinName;
	int value;
	int direction;
	bool exportPin();
	bool unexportPin();
};

#endif

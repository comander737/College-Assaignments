//Andre Bieller
#pragma once
#include <string>
using namespace std;

class device { //Base device class. Contains all variables and functions that all devices share. 
public:
	string deviceName; //Name of device.
	bool deviceOnOff = false;//True or false based on whether the device is on or off. 
	string deviceHealth;//Returns a rating/report based on errors received from device.
	int notifCode;
	bool notifBool = false;

	void notification();//Sents a string to the user notifying them of potential issues. 

	void switchOnOff();//Switch the deviceOnOff bool.

	void checkHealth();//Checks to see if the device returns any errors, adds to notifications. 
};

class thermostat : public device { //Thermostat class, inherits from device. 
public:
	int temperature = 75;//Temperature as an integer. 
	string heatingCooling = "Cooling";//A string that will only be set to "heating" or "cooling" so that the thermostat knows which mode to use. 

	void setHeatingCooling();//Sets the heating and cooling state.

	void setTemperature(int enteredTemp);//Adjusts the temperature integer. 

	void timeActivation(int startTime);//Sets the times whent the thermostat should be active. 
};

class lights : public device { //Lights class. Inherits from device.
public:
	int brightness;//Level of brightness as an integer.
	int time;

	void setBrightness(int enteredBrightness);//Sets the brightness integer. Will only accept 1-5. 

	void timeActivation(int enteredTime);//Sets times at which the lights should be on or off.

};

class television : public device { //Television class, inherits from device. 
public:
	int channel = 5; //Channel as an integer
	int volume = 50; //Volume as an integer

	void setChannel(int enteredChannel);//Sets the channel, accepts a range.

	void setVolume(int enteredVolume);//Sets the volume, accepts 0-100

	void timeActivation(int enteredTime);//Sets the times at which the television should turn on or off. 

};

class security : public device { //Security class, inherits from device, sets base for other security devices.
public:
	bool securityBool = false;
	string disarmCode; //Code needed to disarm security devices.

	void armDisarm(string armCodeEntered); //Checks entered code to turn device on or off.

	string breachNotification(); //Immediate notification if a security system is tripped. 
};

class motionLights : public security { //Motion lights class, inherits from security.
public:
	int sensitivity; //Sensitivity of the lights' motion activiation.

	void setSensitivity(int enteredSensitivity); //Sets the light sensitivity, accepts 1-5.

};

class alarm : public security { //Alarm class. Inherits from security.
public:
	void timeActivation(); //Sets the times for the alarm to be turned on or off without disarm code. 
};
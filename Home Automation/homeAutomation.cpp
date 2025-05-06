//Andre Bieller

#include <string>
#include <iostream>
#include<vector>
#include "homeAutomation.h"
using namespace std;

thermostat Thermostat;

lights Lights;

television Television;

motionLights MotionLights;

alarm Alarm;

vector<string> devices = { Thermostat.deviceName, Lights.deviceName, Television.deviceName, MotionLights.deviceName, Alarm.deviceName };

void initialize() {

	Thermostat.deviceName = "Thermostat";
	Lights.deviceName = "Lights";
	Television.deviceName = "Television";
	MotionLights.deviceName = "Motion Lights";
	Alarm.deviceName = "Alarm";

	cout << "You currently have these devices: " << endl;
	for (int i = 0; i < 5; i++) {
		cout << devices[i] << endl;
	}
	cout << "Which would you like to manage, or would you like to see notificatoins? Enter device name, or 'Notifications'" << endl;
	string deviceInput;
	cin >> deviceInput;
	if (deviceInput == Thermostat.deviceName) {
		cout << "1. Temperature: " << Thermostat.temperature << endl << "2. On/Off: " << Thermostat.deviceOnOff << endl << "3. Heating/Cooling: " << Thermostat.heatingCooling << endl;
		cout << "Enter the number of the property you want to change: " << endl;
		int enteredNum;
		cin >> enteredNum;
		if (enteredNum == 1) {
			int enteredTemp;
			cout << "Enter the temperature you would like: " << endl;
			cin >> enteredTemp;
			Thermostat.setTemperature(enteredTemp);
			initialize();
		}
		if (enteredNum == 2) {
			Thermostat.switchOnOff();
			initialize();
		}
		if (enteredNum == 3) {
			Thermostat.setHeatingCooling();
			initialize();
		}
	}
	else if (deviceInput == Lights.deviceName) {
		cout << "1. On/Off: " << Lights.deviceOnOff << endl << "2. Brightness: " << Lights.brightness << endl << "3. Time Activation: " << Lights.time << endl;
	}
}

void device::notification() {
	string notif;

	if (notifCode == 0) {
		notif = "No Notifications";
		notifBool = false;
	}

	if (notifCode == 1) {
		notif = "Device not connected";
		notifBool = true;
	}

	if (notifCode == 2) {
		notif = "Device update detected";
		notifBool = true;
	}
	
	deviceHealth = notif;

	return;
}

void device::switchOnOff() {
	if (deviceOnOff == false) {
		deviceOnOff = true;
	}

	else if (deviceOnOff == true) {
		deviceOnOff = false;
	}
	return;
}

void device::checkHealth() {
	int health = 0;
	notification();
	if (deviceHealth != "No Notifications") {
		int health = 1;
	}

	return;
}

void thermostat::setHeatingCooling() {
	if (heatingCooling == "Heating") {
		heatingCooling = "Cooling";
	}

	if (heatingCooling == "Cooling") {
		heatingCooling = "Heating";
	}
	return;
}

void thermostat::setTemperature(int enteredTemp) {
	temperature = enteredTemp;

	return;
}

void thermostat::timeActivation(int startTime) {


	return;
}

void security::armDisarm(string armCodeEntered) {

	if (armCodeEntered != disarmCode) {
		cout << "Incorrect alarm code entered";
	}
	else if (securityBool == false) {
		securityBool = true;
	}

	else if (securityBool == true) {
		securityBool = false;
	}
	return;
}

string security::breachNotification() {
	string breachNotif = "Security system has been tripped!";
	return breachNotif;
}

void motionLights::setSensitivity(int enteredSensitivity) {
	if (enteredSensitivity < 1 && enteredSensitivity > 5) {
		cout << "Entered sensitivity out of scope";
	}

	else {
		sensitivity = enteredSensitivity;
	}
}

void alarm::timeActivation() {
	return;
}

void lights::setBrightness(int enteredBrightness) {
	if (enteredBrightness < 1 && enteredBrightness > 100) {
		cout << "Entered value is over 100 or under 1, please re-enter";
	}
	else {
		brightness = enteredBrightness;
	}
}

void lights::timeActivation(int enteredTime) {
	return;
}

void television::setChannel(int enteredChannel) {
	channel = enteredChannel;
}

void television::setVolume(int enteredVolume) {
	if (enteredVolume < 1 && enteredVolume > 100) {
		cout << "Entered volume is over 100 or less than 1, please re-enter";
	}
	else {
		volume = enteredVolume;
	}
}

void television::timeActivation(int enteredTime) {
	return;
}
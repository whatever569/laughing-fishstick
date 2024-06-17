#include "StateMachineInternals.h"
#include "delay.h"
#include "Initializers.h"
#include "User.h"
#include "GameData.h"
#include "Controls.h"
#include "temprature/temp.h"
#include "eeprom/i2c0.h"
#include "pc communication/Microcontroller/uart0.h"
#include <stdio.h>
#include "acuator/servo.h"

using namespace GameData;
using namespace statemachine;
volatile short statemachine::transitionFlag = false;
volatile Event statemachine::currentEvent = (Event)0;

User* User::userSingleton = nullptr;
GameData::InitGameData* GameData::InitGameData::gameDataSingleton = nullptr;
Controls* Controls::controlsSingleton = nullptr;

int main() {
	
	servo_init();
	millis_setup();
	int state = 0;
	servo_lock(0);
	
	while (1) {
		/*
		if (!(milliSecond % 1000)) {
			servo_lock(state);
			state ^= 1;
		}
		*/
	}
	
	
	/*
	StateMachine statemachineInstance;
	StateMachine::stateMachineSingelton = &statemachineInstance;
	User userInstance;
	User::userSingleton = &userInstance;
	InitGameData initgamedataInstance;
	InitGameData::gameDataSingleton = &initgamedataInstance;
	Controls controlInstance;
	Controls::controlsSingleton = &controlInstance;
	 	
	StateMachine::stateMachineSingelton->currentState = S_NO;
	StateMachine::stateMachineSingelton->transition(E_START_STATE_MACHINE);
	
	while (1) {
		if (statemachine::transitionFlag) {
			StateMachine::stateMachineSingelton->transition(statemachine::currentEvent);
			transitionFlag = false;
		}
	}
	*/
	
	/*
	i2c0_init();
	millis_setup();
	
	float temprature;
	
	while (1) {
		if (!(milliSecond % 50)) {
			float temp = temperatureSensor();
			if (temp) {
				temprature = temp;
				char buff[10] = {0};
				sprintf(buff, "%.2f", temprature);
				uart0_send_string(buff);
			}
		}
	}
	*/
	
	return 0;
}

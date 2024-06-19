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
	
	/*
	uart0_init();
	char str[128] = "SNinoW:2|D51.356665, 5.666791C21.22|W0R1P1T25|D51.356215, 5.621791C20.15|W1R1P1T45|E45B4|;";
	uart0_send_string(str);
	delay_ms(1000);
	*/
	
	return 0;
}

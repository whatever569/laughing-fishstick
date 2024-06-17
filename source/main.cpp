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
	
	return 0;
}

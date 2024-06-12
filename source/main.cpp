#include "StateMachineInternals.h"
#include "delay.h"
#include "Initializers.h"
#include "User.h"
#include "GameData.h"
#include "controls.h"
#include "pc communication/Microcontroller/uart0.h"

using namespace GameData;
using namespace statemachine;
short statemachine::transitionFlag = false;
Event statemachine::currentEvent = (Event)0;

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
		
		delay_ms(5);
	}
	
	return 0;
}

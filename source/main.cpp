#include "StateMachineInternals.h"
#include "delay.h"
#include "Initializers.h"
#include "User.h"
#include "GameData.h"

using namespace GameData;
using namespace statemachine;

User* User::userSingleton = nullptr;
GameData::InitGameData* GameData::InitGameData::gameDataSingleton = nullptr;

int main() {
	StateMachine statemachineInstance;
	StateMachine::stateMachineSingelton = &statemachineInstance;
	User userInstance;
	User::userSingleton = &userInstance;
	InitGameData initgamedataInstance;
	InitGameData::gameDataSingleton = &initgamedataInstance;
	
	StateMachine::stateMachineSingelton->currentState = S_NO;
	StateMachine::stateMachineSingelton->transition(E_START_STATE_MACHINE);
	
	delay_ms(100);
	return 0;
}

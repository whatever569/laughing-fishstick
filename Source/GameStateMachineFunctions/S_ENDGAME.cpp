#include <vector>
#include "../GameData.h"
#include "../StateMachineInternals.h"
#include "../display/Display.h"
#include "../User.h"
#include "../GameData.h"
#include "../eeprom/at24c256.h"
#include "../delay.h"
#include "../pc communication/Microcontroller/dataMC.h"

using namespace std;
using namespace statemachine;
using namespace GameData;

StateMachine* StateMachine::stateMachineSingelton = nullptr;

void S_ENDGAME_OnEntry()
{
    StateMachine::stateMachineSingelton->currentState = S_ENDGAME;
    Display::clearScreen();
    Event nextEvent;

    Display::showS_ENDGAMEGameEndedBecauseAllWaypointsWereReached();

	eeprom_write_string(EEPROM_currentAdress, "ENDGAME");
	eeprom_write_uint8_t(EEPROM_currentAdress, GameData::ScoreData::timesDButtonPressed);
	eeprom_write_uint32_t(EEPROM_currentAdress, milliSecond);
	GameDataReturn();
	
    StateMachine::stateMachineSingelton->transition(E_TURNED_OFF);
    
}





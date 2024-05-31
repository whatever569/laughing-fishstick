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

	eepromData[0] = (char)(GameData::ScoreData::timesDButtonPressed / 10)+'0';
    eepromData[1] = (char)(GameData::ScoreData::timesDButtonPressed % 10)+'0';
    eepromData[2] = 'T';
    eepromData[3] = '\0';
    strcpy(eepromData, timeData);
    eepromData[strlen(eepromData)] = '\0';
    eeprom_write_string(EEPROM_currentAdress, eepromData);
	GameDataReturn();
	
    StateMachine::stateMachineSingelton->transition(E_TURNED_OFF);
    
}

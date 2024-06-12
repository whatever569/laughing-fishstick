#include <vector>
#include <stdio.h>
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
	
	char eepromData[12];
	sprintf(eepromData, "E%.3fB%d|", ((float)milliSecond / 1000), GameData::ScoreData::timesDButtonPressed);
    eeprom_write_string(EEPROM_currentAdress, eepromData);
	if (GameDataReturn()) eeprom_flush();
	
	transitionFlag = true;
    currentEvent = E_TURNED_OFF;
}

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "../GameData.h"
#include "../StateMachineInternals.h"
#include "../display/Display.h"
#include "../User.h"
#include "../GameData.h"
#include "../delay.h"
#include "../eeprom/at24c256.h"
#include "../pc communication/Microcontroller/dataMC.h"

using namespace std;
using namespace statemachine;
using namespace GameData;

void S_ERROR_OnEntry()
{
    StateMachine::stateMachineSingelton->currentState = S_ERROR;
    Display::clearScreen();
	char eepromData[12] = {0};
	
   switch(StateMachine::stateMachineSingelton->getErrorSource())
   {
    case E_NO_ERROR_SOURCE_SET:
        Display::showS_ERROR_NO_SOURCE();
        break;
    case E_ERROR_SENDING_DATA:
        Display::showS_ERROR_ERROR_SENDING_DATA_AT_S_ENDGAME();
        break;
    case E_ERROR_DURING_GAME:
        Display::showS_ERROR_ERROR_DURING_GAME();
		
		sprintf(eepromData, "W%dR%dP%dT%ld|",User::userSingleton->currentWayPointNumber, 
										  InitGameData::gameDataSingleton->wayPoints[User::userSingleton->currentWayPointNumber].getIsReached(),
										  InitGameData::gameDataSingleton->wayPoints[User::userSingleton->currentWayPointNumber].getIsPuzzleSuccess(),
									      milliSecond);
		eeprom_write_string(EEPROM_currentAdress, eepromData);
		break;
    case E_INIT_ERROR:
        Display::showS_ERROR_ERROR_INIT();
        break;
    default:
        Display::showS_ERROR_NO_SOURCE();
        break;
   }
   
   memset(eepromData, 0, sizeof(eepromData));
   sprintf(eepromData, "E%.3fB%d|", ((float)milliSecond / 1000), GameData::ScoreData::timesDButtonPressed);
   eeprom_write_string(EEPROM_currentAdress, eepromData);
   GameDataReturn();

   //TODO have a way to get out the error state.
}
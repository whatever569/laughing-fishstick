#include <vector>
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
	char timeData[8] = {0};
	
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
		
		eepromData[0] = 'W';
		eepromData[1] = (char)(User::userSingleton->currentWayPointNumber+'0');
		eepromData[2] = ' ';
		eepromData[3] = (InitGameData::gameDataSingleton->wayPoints[User::userSingleton->currentWayPointNumber].getIsReached()) ? '1' : '0';
		eepromData[4] = (InitGameData::gameDataSingleton->wayPoints[User::userSingleton->currentWayPointNumber].getIsPuzzleSuccess()) ? '1' : '0';
		sprintf(timeData, "%ld", milliSecond);
		strcat(eepromData, timeData);
		eepromData[strlen(eepromData)] = '\0';
		eeprom_write_string(EEPROM_currentAdress, eepromData);
		break;
    case E_INIT_ERROR:
        Display::showS_ERROR_ERROR_INIT();
        break;
    default:
        Display::showS_ERROR_NO_SOURCE();
        break;
   }
   
   eepromData[0] = (char)(GameData::ScoreData::timesDButtonPressed / 10)+'0';
   eepromData[1] = (char)(GameData::ScoreData::timesDButtonPressed % 10)+'0';
   eepromData[2] = 'T';
   eepromData[3] = '\0';
   strcpy(eepromData, timeData);
   eepromData[strlen(eepromData)] = '\0';
   eeprom_write_string(EEPROM_currentAdress, eepromData);
   GameDataReturn();

   //TODO have a way to get out the error state.
}
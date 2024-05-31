#include <vector>
#include "../GameData.h"
#include "../Initializers.h"
#include "../StateMachineInternals.h"
#include "../display/Display.h"
#include "../User.h"
#include "../pc communication/Microcontroller/dataMC.h"
#include "../eeprom/at24c256.h"
#include <string.h>
	
using namespace std;
using namespace statemachine;
using namespace GameData;

void S_INIT_OnEntry()
{
    initializeModules();
    bool isDataGottenSuccessfully;
    Event nextEvent;
    StateMachine::stateMachineSingelton->currentState = S_INIT;
    Display::clearScreen();
    Display::showINITScreen();

	isDataGottenSuccessfully = GameDataInit();	//i dont really have error checking but what we can do is, tranmit it back to pc so admin can confirm
    if(isDataGottenSuccessfully)
    {
        nextEvent = E_INIT_SUCCESS;
    }else{
        nextEvent = E_INIT_ERROR;
        StateMachine::stateMachineSingelton->setErrorSource(E_INIT_ERROR);
    }
	char eepromData[20];
	strcpy(eepromData, User::userSingleton->username);
	strcat(eepromData, "W:");
	eepromData[strlen(eepromData)] = (char)(InitGameData::gameDataSingleton->wayPoints.size()+'0');
	eepromData[strlen(eepromData)] = '\0';
	
	eeprom_write_string(EEPROM_currentAdress, eepromData);	
	
    ScoreData::timesDButtonPressed = 0;
    StateMachine::stateMachineSingelton->transition(nextEvent);
}

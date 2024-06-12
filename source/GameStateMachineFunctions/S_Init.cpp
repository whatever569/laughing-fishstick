#include <vector>
#include "../GameData.h"
#include "../Initializers.h"
#include "../StateMachineInternals.h"
#include "../display/Display.h"
#include "../User.h"
#include "../pc communication/Microcontroller/dataMC.h"
#include "../eeprom/at24c256.h"
#include "../Controls.h"
#include <string.h>
#include <stdio.h>
#include "acuator/servo.h"
	
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
	servo_lock(0);
	
	Controls::controlsSingleton->setFunctionsForButtons(Controls::doNothing, 		//A button
                                                        Controls::doNothing, 		//B button
	Controls::doNothing,   //C button
                                                        Controls::doNothing);
	
	isDataGottenSuccessfully = GameDataInit();	//i dont really have error checking but what we can do is, tranmit it back to pc so admin can confirm
	
    if(isDataGottenSuccessfully) {
		servo_lock(1);
		char eepromData[20];
		sprintf(eepromData, "%sW:%d|", User::userSingleton->username, sizeof(InitGameData::gameDataSingleton->wayPoints)/sizeof(WayPoint));
		eeprom_write_string(EEPROM_currentAdress, eepromData);	
		
		ScoreData::timesDButtonPressed = 0;
		transitionFlag = true;
		currentEvent = E_INIT_SUCCESS;
    }
	else {
        nextEvent = E_INIT_ERROR;
        StateMachine::stateMachineSingelton->setErrorSource(E_INIT_ERROR);
    }	
}

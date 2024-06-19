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

void continueInit(void);

void S_INIT_OnEntry()
{
	initializeModules();
    bool isDataGottenSuccessfully;
    Event nextEvent;
    StateMachine::stateMachineSingelton->currentState = S_INIT;
    Display::clearScreen();
    Display::showINITScreen();
	servo_lock(0);
	//eeprom_flush();
	EEPROM_currentAdress = 0;
	
	Controls::controlsSingleton->setFunctionsForButtons(continueInit, 				//A button
                                                        Controls::doNothing, 		//B button
														Controls::doNothing,   		//C button
                                                        Controls::doNothing);		//D button
	
	isDataGottenSuccessfully = GameDataInit();	//i dont really have error checking but what we can do is, tranmit it back to pc so admin can confirm
	if (!isDataGottenSuccessfully) GameDataDefault();
	
    //if(isDataGottenSuccessfully) {
		
	char eepromData[20];
	sprintf(eepromData, "%sW:%d|", User::userSingleton->username, sizeof(InitGameData::gameDataSingleton->wayPoints)/sizeof(WayPoint));
	eeprom_write_string(EEPROM_currentAdress, eepromData);	
	
	ScoreData::timesDButtonPressed = 0;
		
	Display::showCloseBox();
   
    //}
	
	/*
	else {
        nextEvent = E_INIT_ERROR;
        StateMachine::stateMachineSingelton->setErrorSource(E_INIT_ERROR);
    }
	*/	
}

void continueInit (void) {
	servo_lock(1);
	transitionFlag = true;
	currentEvent = E_INIT_SUCCESS;
}
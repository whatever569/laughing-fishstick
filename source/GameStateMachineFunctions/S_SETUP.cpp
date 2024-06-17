#include <vector>
#include "../eeprom/at24c256.h"
#include "../GameData.h"
#include "../StateMachineInternals.h"
#include "../display/Display.h"
#include "../User.h"
#include "../GameData.h"
#include "../delay.h"
#include <stdio.h>

using namespace std;
using namespace statemachine;
using namespace GameData;

void S_SETUP_OnEntry()
{
	char eepromData[15] = {0};
	sprintf(eepromData, "W%dR%dP%dT%ld|",User::userSingleton->currentWayPointNumber, 
										  InitGameData::gameDataSingleton->wayPoints[User::userSingleton->currentWayPointNumber].getIsReached(),
										  InitGameData::gameDataSingleton->wayPoints[User::userSingleton->currentWayPointNumber].getIsPuzzleSuccess(),
									      milliSecond);
	eeprom_write_string(EEPROM_currentAdress, eepromData);
	
    StateMachine::stateMachineSingelton->currentState = S_SETUP;
    Event nextEvent;
	
    // if user has finished all the waypoints
    if (User::userSingleton->currentWayPointNumber + 1 == User::userSingleton->TotalWayPoints)
    {
        nextEvent = E_ALL_WAYPOINTS_REACHED;
    }
    else if (User::userSingleton->currentWayPointNumber + 1 < User::userSingleton->TotalWayPoints)
    {
        nextEvent = E_NEW_WAYPOINT;
        User::userSingleton->currentWayPointNumber++;
    }
	else 
	{
		nextEvent = E_ERROR_DURING_GAME;
	}

	currentEvent = nextEvent;
	StateMachine::stateMachineSingelton->transition(statemachine::currentEvent);
}

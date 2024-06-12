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
	sprintf(eepromData, "W%dR1P1T%ld|", User::userSingleton->currentWayPointNumber, milliSecond);
	eeprom_write_string(EEPROM_currentAdress, eepromData);
	
    StateMachine::stateMachineSingelton->currentState = S_SETUP;
    Display::clearScreen();
    Display::showLoading();
    Event nextEvent;
    // if user has finished all the waypoints
    if (User::userSingleton->currentWayPointNumber == sizeof(InitGameData::gameDataSingleton->wayPoints)/sizeof(WayPoint))
    {
        nextEvent = E_ALL_WAYPOINTS_REACHED;
    }
    else if (User::userSingleton->currentWayPointNumber < sizeof(InitGameData::gameDataSingleton->wayPoints)/sizeof(WayPoint))
    {
        nextEvent = E_NEW_WAYPOINT;
        User::userSingleton->currentWayPointNumber++;
    }

	currentEvent = nextEvent;
	transitionFlag = true;
}

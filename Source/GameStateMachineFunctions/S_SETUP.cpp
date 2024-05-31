#include <vector>
#include <string.h>
#include "../eeprom/at24c256.h"
#include "../GameData.h"
#include "../StateMachineInternals.h"
#include "../display/Display.h"
#include "../User.h"
#include "../GameData.h"
#include "../delay.h"

using namespace std;
using namespace statemachine;
using namespace GameData;

void S_SETUP_OnEntry()
{
	char eepromData[12] = {0};
	char timeData[8] = {0};
	eepromData[0] = 'W';
	eepromData[1] = (char)(User::userSingleton->currentWayPointNumber+'0'-1);
	sprintf(timeData, "%ld", milliSecond);
	strcat(eepromData, " 11");
	strcat(eepromData, timeData);
	eepromData[strlen(eepromData)] = '\0';
	eeprom_write_string(EEPROM_currentAdress, eepromData);
	
    StateMachine::stateMachineSingelton->currentState = S_SETUP;
    Display::clearScreen();
    Display::showLoading();
    Event nextEvent;
    // if user has finished all the waypoints
    if (User::userSingleton->currentWayPointNumber == InitGameData::gameDataSingleton->wayPoints.size())
    {
        nextEvent = E_ALL_WAYPOINTS_REACHED;
    }
    else if (User::userSingleton->currentWayPointNumber < InitGameData::gameDataSingleton->wayPoints.size())
    {
        nextEvent = E_NEW_WAYPOINT;
        User::userSingleton->currentWayPointNumber++;
    }

    StateMachine::stateMachineSingelton->transition(nextEvent);
}

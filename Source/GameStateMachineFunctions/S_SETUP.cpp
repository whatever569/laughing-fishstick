#include <vector>
#include "../GameData.h"
#include "../StateMachineInternals.h"
#include "../display/Display.h"
#include "../User.h"
#include "../GameData.h"

using namespace std;
using namespace statemachine;
using namespace GameData;

void S_SETUP_OnEntry()
{
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

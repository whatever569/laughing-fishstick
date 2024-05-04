
#include <vector>
#include "../GameData.hpp"
#include "../StateMachineInternals.hpp"
#include "../Display.hpp"
#include "../User.hpp"
#include "../GameData.hpp"

using namespace std;
using namespace statemachine;
using namespace GameData;
void S_SETUP_OnEntry()
{
    StateMachine::stateMachineSingelton->currentState = S_SETUP;
    Display::showNothingForNow();
    Event nextEvent;
    //if user has finished all the waypoints
    if(User::userSingelton->currentWayPointNumber == InitGameData::gameDataSingleton->wayPoints.size())
    {
        nextEvent = E_ALL_WAYPOINTS_REACHED;
    }else if (User::userSingelton->currentWayPointNumber < InitGameData::gameDataSingleton->wayPoints.size())
    {
        nextEvent = E_NEW_WAYPOINT;
        User::userSingelton->currentWayPointNumber++;
    }

    StateMachine::stateMachineSingelton->transition(nextEvent);
}





using namespace std;
using namespace statemachine;
#include <vector>
#include "../GameData.hpp"
#include "../StateMachineInternals.hpp"
#include "../Display.hpp"
#include "../Controls.hpp"
#include "../User.hpp"
const int nSecondsShowDirectionTimer = 2;
using namespace GameData;
const double hotColdGameThreshold = 25.0;
void S_SEARCH_OnEntry()
{
    StateMachine::stateMachineSingelton->currentState = S_SEARCH;
    Display::showSEARCHScreen();

    Controls::controlsSingleton->setFunctionsForButtons(
        Controls::doNothing,
        Controls::doNothing,
        Controls::doNothing,
        showDir
    );

    //TODO:: create a timer that generates an interrupt every 5 seconds when >100meters away and every 1 second when < (if it was found that that approach is faster and more performant)
    //each time the timer does an interrupt call interruptFunctionS_SEARCH
}


//DEPRECATED
// void showDirectionsForNSeconds()
// {
//     //make a timer and show directions screen for nSecondsShowDirectionTimer seconds
//     //update user object
//     User::userSingelton->timeDirectionButtonPressed++;
//     //go back to the normal SEARCH screen again
//     Display::showSEARCHScreen();
// }

void interruptFunctionS_SEARCH()
{
    GPSLocation currentlocation = User::userSingelton->getUsersCurrentLocation();

    if((currentlocation.distanceTo(InitGameData::
                                            gameDataSingleton->wayPoints
                                            [User::userSingelton->currentWayPointNumber]
                                            .getLocation())) == hotColdGameThreshold)
    {
        StateMachine::stateMachineSingelton->transition(E_CLOSE_PROXIMITY);
    }
}

void showDir()
{
    Display::showScreenForNSeconds(nSecondsShowDirectionTimer, Display::showDIRECTIONSEARCHscreen, Display::showSEARCHScreen);
}
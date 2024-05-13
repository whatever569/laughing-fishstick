#include <vector>
#include "../GameData.hpp"
#include "../StateMachineInternals.hpp"
#include "../Display.hpp"
#include "../Controls.hpp"
#include "../User.hpp"
#include "../PIT.hpp"
using namespace std;
using namespace statemachine;
using namespace GameData;
const int nSecondsShowDirectionTimer = 2;
const double hotColdGameThreshold = 25.0;
const double distanceAboveWhichInterruptsAreDoneSlower = 100.0;
const double slowInterruptFrequency = 0.2;
const double fastInterruptFrequency = 1.0;
void S_SEARCH_OnEntry()
{
    StateMachine::stateMachineSingelton->currentState = S_SEARCH;
    Display::clearScreen();
    Display::showSEARCHScreen();

    PITObject::PITSingleton = new PITObject(slowInterruptFrequency, interruptFunctionS_SEARCH);

    Controls::controlsSingleton->setFunctionsForButtons(
        Controls::doNothing,
        Controls::doNothing,
        Controls::doNothing,
        showDir);
}

void interruptFunctionS_SEARCH()
{
    GPSLocation currentlocation = User::userSingelton->getUsersCurrentLocation();
    double distance = (currentlocation.distanceTo(InitGameData::
                                                      gameDataSingleton->wayPoints
                                                          [User::userSingelton->currentWayPointNumber]
                                                              .getLocation()));
    if (distance == hotColdGameThreshold)
    {
        PITObject::PITSingleton->deleteInstance();
        StateMachine::stateMachineSingelton->transition(E_CLOSE_PROXIMITY);
    }
    else if (distance > distanceAboveWhichInterruptsAreDoneSlower)
    {
        PITObject::PITSingleton->setInterruptFrequency(slowInterruptFrequency);
    }
    else
    {
        PITObject::PITSingleton->setInterruptFrequency(fastInterruptFrequency);
    }
}

void showDir()
{
    Display::showScreenForNSeconds(nSecondsShowDirectionTimer, Display::showDIRECTIONSEARCHscreen, Display::showSEARCHScreen);
}

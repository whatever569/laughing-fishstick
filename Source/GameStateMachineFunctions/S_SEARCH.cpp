#include "../GameData.h"
#include "../StateMachineInternals.h"
#include "../display/Display.h"
#include "../Controls.h"
#include "../User.h"
#include "../delay.h"

using namespace std;
using namespace statemachine;
using namespace GameData;

const int nSecondsShowDirectionTimer = 2;
const double hotColdGameThreshold = 25.0;
const double distanceAboveWhichInterruptsAreDoneSlower = 100.0;

void showDir();

void S_SEARCH_OnEntry()
{
    StateMachine::stateMachineSingelton->currentState = S_SEARCH;
    Display::clearScreen();
    Display::showSEARCHScreen();

	pitFunction = S_search;

    Controls::controlsSingleton->setFunctionsForButtons(
        Controls::doNothing,
        Controls::doNothing,
        Controls::doNothing,
        showDir);
}

void interruptFunctionS_SEARCH()
{
    GPSLocation currentlocation = User::userSingleton->getUsersCurrentLocation();
    double distance = (currentlocation.distanceTo(InitGameData::
                                                      gameDataSingleton->wayPoints
                                                          [User::userSingleton->currentWayPointNumber]
                                                              .getLocation()));
    if (distance == hotColdGameThreshold)
    {
        StateMachine::stateMachineSingelton->transition(E_CLOSE_PROXIMITY);
    }
    else if (distance > distanceAboveWhichInterruptsAreDoneSlower)
    {
        PIT->CHANNEL[0].LDVAL = PIT_LDVAL_TSV((24e6 / SLOWINTERRUPTFREQUENCY) - 1);
    }
    else
    {
        PIT->CHANNEL[0].LDVAL = PIT_LDVAL_TSV((24e6 / FASTINTERRUPTFREQUENCY) - 1);
    }
}

void showDir()
{
    GPSLocation currentlocation = User::userSingleton->getUsersCurrentLocation();
    GPSLocation::Direction dir = currentlocation.getDirection(InitGameData::
                                                                  gameDataSingleton->wayPoints
                                                                      [User::userSingleton->currentWayPointNumber]
                                                                          .getLocation());
    switch (dir)
    {
    case (GPSLocation::LEFT):
        Display::showScreenForNSeconds(nSecondsShowDirectionTimer, Display::showLeftArrow, Display::clearScreen);
        break;
    case (GPSLocation::RIGHT):
        Display::showScreenForNSeconds(nSecondsShowDirectionTimer, Display::showRightArrow, Display::clearScreen);
        break;
    case (GPSLocation::UP):
        Display::showScreenForNSeconds(nSecondsShowDirectionTimer, Display::showUpArrow, Display::clearScreen);
        break;
    case (GPSLocation::DOWN):
        Display::showScreenForNSeconds(nSecondsShowDirectionTimer, Display::showDownArrow, Display::clearScreen);
        break;
    }

    ScoreData::timesDButtonPressed++;
}

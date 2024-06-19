#include <stdio.h>
#include "../GameData.h"
#include "../StateMachineInternals.h"
#include "../display/Display.h"
#include "../Controls.h"
#include "../User.h"
#include "../delay.h"
#include "../pc communication/Microcontroller/uart0.h"

using namespace std;
using namespace statemachine;
using namespace GameData;
const int nSecondsShowDirectionTimer = 2;
const double hotColdGameThreshold = 50.0;
const double distanceAboveWhichInterruptsAreDoneSlower = 100.0;

void interruptFunctionS_SEARCH();
void showDir();

void S_SEARCH_OnEntry()
{
    StateMachine::stateMachineSingelton->currentState = S_SEARCH;
    Display::clearScreen();
    Display::showSEARCHScreen();

	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK;
	pitFunction = pitfunction_search;

    Controls::controlsSingleton->setFunctionsForButtons(
        Controls::doNothing,
        Controls::doNothing,
		Controls::doNothing,
        showDir);
}

void interruptFunctionS_SEARCH()
{
	char coordinates[30] = {0};
	User::userSingleton->setUsersCurrentLocation(coordinates);
	
    GPSLocation currentlocation = User::userSingleton->getUsersCurrentLocation();
    double distance = (currentlocation.distanceTo(InitGameData::gameDataSingleton->
												  wayPoints[User::userSingleton->currentWayPointNumber]
												  .getLocation()));
	//Display::testDistance(distance, 2, Display::showSEARCHScreen);
	
    if (distance <= hotColdGameThreshold)
    {
        currentEvent = E_CLOSE_PROXIMITY;
		transitionFlag = true;
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
	
	while (!currentlocation.getIsConnected()) {
		char coordinates[30] = {0};
		delay_ms(500);
		Display::showAwaitingReconnection();
		User::userSingleton->setUsersCurrentLocation(coordinates);
		currentlocation = User::userSingleton->getUsersCurrentLocation();
	}
	
	GPSLocation::Direction dir = currentlocation.getDirection(InitGameData::
															  gameDataSingleton->wayPoints
																  [User::userSingleton->currentWayPointNumber]
																	  .getLocation());
	switch (dir)
	{
	case (GPSLocation::LEFT):
		Display::showScreenForNSeconds(nSecondsShowDirectionTimer, Display::showLeftArrow, Display::showSEARCHScreen);
		break;
	case (GPSLocation::RIGHT):
		Display::showScreenForNSeconds(nSecondsShowDirectionTimer, Display::showRightArrow, Display::showSEARCHScreen);
		break;
	case (GPSLocation::UP):
		Display::showScreenForNSeconds(nSecondsShowDirectionTimer, Display::showUpArrow, Display::showSEARCHScreen);
		break;
	case (GPSLocation::DOWN):
		Display::showScreenForNSeconds(nSecondsShowDirectionTimer, Display::showDownArrow, Display::showSEARCHScreen);
		break;
	}
	
	ScoreData::timesDButtonPressed++;
}

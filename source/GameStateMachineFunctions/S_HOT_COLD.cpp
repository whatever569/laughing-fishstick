#include <vector>
#include "../GameData.h"
#include "../StateMachineInternals.h"
#include "../display/Display.h"
#include "../Controls.h"
#include "../User.h"
#include "../delay.h"
#include "../eeprom/at24c256.h"

using namespace GameData;
using namespace std;
using namespace statemachine;

// This is when the game goes to the S_SEARCH state again
const double hotColdExitThreshold = 70.0;
const double reachedThreshold = 10.0;
GPSLocation wpLocation;
const double part = hotColdExitThreshold / 4.0;  // Calculate each part size
const int secondstoShowNotCloseAnymoreScreen = 4;

void timerInterruptHotCold();

void S_HOT_COLD_OnEntry() {
    StateMachine::stateMachineSingelton->currentState = S_HOT_COLD;
    wpLocation = InitGameData::gameDataSingleton->wayPoints[User::userSingleton->currentWayPointNumber].getLocation();
	
	Controls::controlsSingleton->setFunctionsForButtons(
        Controls::doNothing,
        Controls::doNothing,
		Controls::doNothing,
		Controls::doNothing);

    PIT->CHANNEL[1].LDVAL = PIT_LDVAL_TSV((24e6 / INTERRUPTFREQUENCY) - 1);
	pitFunction = pitfunction_hotcold;
}

void timerInterruptHotCold() {
	char coordinates[30] = {0};
	User::userSingleton->setUsersCurrentLocation(coordinates);
	
    GPSLocation currentLocation = User::userSingleton->getUsersCurrentLocation();
    double distance = currentLocation.distanceTo(wpLocation);
	//Display::testDistance(distance, 2, Display::showAwaitingReconnection);
	//delay_ms(2000);

    if (distance >= hotColdExitThreshold) {
        Display::showScreenForNSeconds(secondstoShowNotCloseAnymoreScreen, Display::showS_HOT_COLDNotCloseAnymore, Display::showLoading);
		transitionFlag = true;
		currentEvent = E_NOT_CLOSE_ANYMORE;
    } else if (distance > 3 * part) {
        Display::clearScreen();
        Display::showS_HOT_COLDVeryColdStatus();
    } else if (distance > 2 * part) {
        Display::clearScreen();
        Display::showS_HOT_COLDColdStatus();
    } else if (distance > part) {
        Display::clearScreen();
        Display::showS_HOT_COLDWarmStatus();
    } else if (distance > reachedThreshold) {
        Display::clearScreen();
        Display::showS_HOT_COLDHotStatus();
    } else if (distance >= 0) {
		PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TIE_MASK & ~PIT_TCTRL_TEN_MASK;		//turn off pit timer
        InitGameData::gameDataSingleton->wayPoints[User::userSingleton->currentWayPointNumber].setIsReached(true);
		transitionFlag = true;
		currentEvent = E_WAYPOINT_REACHED;
    }
}


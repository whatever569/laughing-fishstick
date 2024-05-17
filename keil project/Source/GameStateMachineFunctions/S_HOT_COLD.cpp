#include <vector>
#include "../GameData.hpp"
#include "../StateMachineInternals.hpp"
#include "../Display.hpp"
#include "../Controls.hpp"
#include "../User.hpp"
#include "../PIT.hpp"

using namespace GameData;
using namespace std;
using namespace statemachine;

// This is when the game goes to the S_SEARCH state again
const double hotColdExitThreshold = 35.0;
const double reachedThreshold = 5.0;
GPSLocation wpLocation;
const double part = hotColdExitThreshold / 4.0;  // Calculate each part size
const int secondstoShowNotCloseAnymoreScreen = 3;
const double interruptFrequency = 1.5;
void timerInterruptHotCold();
void S_HOT_COLD_OnEntry() {
    StateMachine::stateMachineSingelton->currentState = S_HOT_COLD;
    wpLocation = InitGameData::gameDataSingleton->wayPoints[User::userSingleton->currentWayPointNumber].getLocation();

    PITObject::PITSingleton = new PITObject(interruptFrequency, timerInterruptHotCold);
}

void timerInterruptHotCold() {

    GPSLocation currentLocation = User::userSingleton->getUsersCurrentLocation();
    double distance = currentLocation.distanceTo(wpLocation);

    if (distance >= hotColdExitThreshold) {
        Display::showScreenForNSeconds(secondstoShowNotCloseAnymoreScreen, Display::showS_HOT_COLDNotCloseAnymore, Display::showLoading);
        StateMachine::stateMachineSingelton->transition(E_NOT_CLOSE_ANYMORE);
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
        InitGameData::gameDataSingleton->wayPoints[User::userSingleton->currentWayPointNumber].setIsReached(true);
        PITObject::PITSingleton->deleteInstance();
        StateMachine::stateMachineSingelton->transition(E_WAYPOINT_REACHED);
    }
}


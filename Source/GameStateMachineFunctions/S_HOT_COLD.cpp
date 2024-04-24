using namespace std;
using namespace statemachine;
#include <vector>
#include "../GameData.hpp"
#include "../StateMachineInternals.hpp"
#include "../Display.hpp"
#include "../Controls.hpp"
#include "../User.hpp"
using namespace GameData;

// This is when the game goes to the S_SEARCH state again
const double hotColdExitThreshold = 35.0;
const double reachedThreshold = 5.0;

void S_HOT_COLD_OnEntry() {
    StateMachine::stateMachineSingelton->currentState = S_HOT_COLD;
    // Setup a timer here that calls timerInterruptHotCold() every second
}

void timerInterruptHotCold() {
    GPSLocation currentLocation = User::userSingelton->getUsersCurrentLocation();
    GPSLocation wpLocation = InitGameData::gameDataSingleton->wayPoints[User::userSingelton->currentWayPointNumber].getLocation();
    double distance = currentLocation.distanceTo(wpLocation);
    
    const double part = hotColdExitThreshold / 4.0;  // Calculate each part size

    if (distance >= hotColdExitThreshold) {
        StateMachine::stateMachineSingelton->transition(E_NOT_CLOSE_ANYMORE);
    } else if (distance > 3 * part) {
        Display::showS_HOT_COLDVeryColdStatus();
    } else if (distance > 2 * part) {
        Display::showS_HOT_COLDColdStatus();
    } else if (distance > part) {
        Display::showS_HOT_COLDWarmStatus();
    } else if (distance > reachedThreshold) {
        Display::showS_HOT_COLDHotStatus();
    } else if (distance >= 0) {
        InitGameData::gameDataSingleton->wayPoints[User::userSingelton->currentWayPointNumber].setIsReached(true);
        StateMachine::stateMachineSingelton->transition(E_WAYPOINT_REACHED);
    }
}


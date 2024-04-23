using namespace std;
using namespace statemachine;
#include <vector>
#include "../GameData.hpp"
#include "../StateMachineInternals.hpp"
#include "../Display.hpp"
#include "../Controls.hpp"
#include "../User.hpp"
const int nSecondsShowDirectionTimer = 2;

void S_SEARCH_OnEntry()
{
    StateMachine::stateMachineSingelton->currentState = S_SEARCH;
    showSEARCHScreen();

    Controls::controlsSingleton->setFunctionsForButtons(
        Controls::doNothing,
        Controls::doNothing,
        Controls::doNothing,
        showDirectionsForNSeconds
    );

    //check for distance and other events here
}


//N will be 2 here
void showDirectionsForNSeconds()
{
    //make a timer and show directions screen for nSecondsShowDirectionTimer seconds
    //update user object
    User::userSingelton->timeDirectionButtonPressed++;
    //go back to the normal SEARCH screen again
    showSEARCHScreen();
}
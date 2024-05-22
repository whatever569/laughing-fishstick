#include <vector>
#include "../GameData.h"
#include "../Initializers.h"
#include "../StateMachineInternals.h"
#include "../Display.h"
#include "../User.h"
using namespace std;
using namespace statemachine;
void S_INIT_OnEntry()
{
    initializeModules();
    bool isDataGottenSuccessfully;
    Event nextEvent;
    StateMachine::stateMachineSingelton->currentState = S_INIT;
    Display::clearScreen();
    Display::showINITScreen();

    //TODO: Get data and initialize user object
    if(isDataGottenSuccessfully)
    {
        nextEvent = E_INIT_SUCCESS;
    }else{
        nextEvent = E_INIT_ERROR;
        StateMachine::stateMachineSingelton->setErrorSource(E_INIT_ERROR);
    }
    StateMachine::stateMachineSingelton->transition(nextEvent);
}





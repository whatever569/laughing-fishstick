using namespace std;
using namespace statemachine;
#include <vector>
#include "../GameData.hpp"
#include "../Initializers.hpp"
#include "../StateMachineInternals.hpp"
#include "../Display.hpp"

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





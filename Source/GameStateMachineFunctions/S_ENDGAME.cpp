#include <vector>
#include "../GameData.h"
#include "../StateMachineInternals.h"
#include "../Display.h"
#include "../User.h"
#include "../GameData.h"
using namespace std;
using namespace statemachine;
using namespace GameData;

StateMachine* StateMachine::stateMachineSingelton = nullptr;

void S_ENDGAME_OnEntry()
{
    StateMachine::stateMachineSingelton->currentState = S_ENDGAME;
    Display::clearScreen();
    Event nextEvent;

    Display::showS_ENDGAMEGameEndedBecauseAllWaypointsWereReached();

    //TODO transfer all data when connected to pc

    StateMachine::stateMachineSingelton->transition(E_TURNED_OFF);
    
}





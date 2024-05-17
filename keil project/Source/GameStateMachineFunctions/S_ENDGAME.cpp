#include <vector>
#include "../GameData.hpp"
#include "../StateMachineInternals.hpp"
#include "../Display.hpp"
#include "../User.hpp"
#include "../GameData.hpp"
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





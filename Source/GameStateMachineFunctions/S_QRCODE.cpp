using namespace std;
using namespace statemachine;
#include <vector>
#include "../GameData.hpp"
#include "../StateMachineInternals.hpp"
#include "../Display.hpp"
#include "../Controls.hpp"

void S_QRCODE_OnEntry()
{
    Event nextEvent;
    StateMachine::stateMachineSingelton->currentState = S_QRCODE;
    while(!isCPressed()){}
    nextEvent = E_CONTINUE_BUTTON;
    StateMachine::stateMachineSingelton->transition(nextEvent);

}

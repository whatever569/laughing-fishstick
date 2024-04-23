using namespace std;
using namespace statemachine;
#include <vector>
#include "../GameData.hpp"
#include "../StateMachineInternals.hpp"
#include "../Display.hpp"
#include "../Controls.hpp"

void S_QRCODE_OnEntry()
{
    showQRCODEScreen();
    StateMachine::stateMachineSingelton->currentState = S_QRCODE;
    Controls::controlsSingleton->setFunctionsForButtons(Controls::controlsSingleton->doNothing, //A button
                                                        Controls::controlsSingleton->doNothing, //B button
                                                        switchToNextStateSSEARCH,               //C button
                                                        Controls::controlsSingleton->doNothing);//D button
}

void switchToNextStateSSEARCH()
{
    StateMachine::stateMachineSingelton->transition(E_CONTINUE_BUTTON);
}
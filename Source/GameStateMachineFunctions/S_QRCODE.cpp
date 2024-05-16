
#include <vector>
#include "../GameData.hpp"
#include "../StateMachineInternals.hpp"
#include "../Display.hpp"
#include "../Controls.hpp"

using namespace std;
using namespace statemachine;
void switchToNextStateSSEARCH();

void S_QRCODE_OnEntry()
{
    Display::clearScreen();
    Display::showQRCODEScreen();
    StateMachine::stateMachineSingelton->currentState = S_QRCODE;
    Controls::controlsSingleton->setFunctionsForButtons(Controls::doNothing, //A button
                                                        Controls::doNothing, //B button
                                                        switchToNextStateSSEARCH,               //C button
                                                        Controls::doNothing);//D button
}

void switchToNextStateSSEARCH()
{
    StateMachine::stateMachineSingelton->transition(E_CONTINUE_BUTTON);
}

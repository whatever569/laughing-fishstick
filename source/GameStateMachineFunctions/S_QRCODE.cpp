#include <vector>
#include "../GameData.h"
#include "../StateMachineInternals.h"
#include "../display/Display.h"
#include "../Controls.h"

using namespace std;
using namespace statemachine;
void switchToNextStateSSEARCH();

Controls* Controls::controlsSingleton = nullptr;

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

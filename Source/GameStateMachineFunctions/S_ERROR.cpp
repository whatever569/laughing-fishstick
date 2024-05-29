#include <vector>
#include "../GameData.h"
#include "../StateMachineInternals.h"
#include "../display/Display.h"
#include "../User.h"
#include "../GameData.h"

using namespace std;
using namespace statemachine;
using namespace GameData;
void S_ERROR_OnEntry()
{
    StateMachine::stateMachineSingelton->currentState = S_ERROR;
    Display::clearScreen();
   switch(StateMachine::stateMachineSingelton->getErrorSource())
   {
    case E_NO_ERROR_SOURCE_SET:
        Display::showS_ERROR_NO_SOURCE();
        break;
    case E_ERROR_SENDING_DATA:
        Display::showS_ERROR_ERROR_SENDING_DATA_AT_S_ENDGAME();
        break;
    case E_ERROR_DURING_GAME:
        Display::showS_ERROR_ERROR_DURING_GAME();
    case E_INIT_ERROR:
        Display::showS_ERROR_ERROR_INIT();
        break;
    default:
        Display::showS_ERROR_NO_SOURCE();
        break;
   }

   //TODO have a way to get out the error state.
}
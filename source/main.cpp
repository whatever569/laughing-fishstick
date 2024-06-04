#include "pc communication/Microcontroller/uart0.h"
#include "delay.h"
#include "eeprom/at24c256.h"
#include "pc communication/Microcontroller/dataMC.h"
#include "StateMachineInternals.h"

 int main() {
	//consider putting this in S_INIT to keep the clean software structure of the state mahcine if they don't explicitly need to be here
	delete statemachine::StateMachine::stateMachineSingelton;
	statemachine::StateMachine::stateMachineSingelton = new statemachine::StateMachine;
	
	statemachine::StateMachine::stateMachineSingelton->currentState = statemachine::S_NO;
	
	//this line causes bkpt error with this specific event, other events are fine
	statemachine::StateMachine::stateMachineSingelton->transition(statemachine::E_ENTER_STATE_MACHINE);

	//looping back to S_INIT or some other state is done in the state machine, there is should be no while loop as the software archeticture is event based

	return 0;
}

#ifndef STATEMACHINEINTERNALS_H
#define STATEMACHINEINTERNALS_H

namespace statemachine
{
    enum State
    {
        S_NO,
        S_INIT,
        S_QRCODE,
    };

    enum Event
    {
        E_INIT_ERROR,
        E_INIT_SUCCESS,
        E_CONTINUE_BUTTON
    };
    
    class StateMachine
    {
        public:
            static StateMachine* stateMachineSingelton;
            State currentState = S_NO;
        //TODO create a transition table
        void transition(Event e)
            {
                //TODO
            }

    };
}
#endif
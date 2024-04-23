#ifndef STATEMACHINEINTERNALS_H
#define STATEMACHINEINTERNALS_H

namespace statemachine
{
    enum State
    {
        S_NO,
        S_INIT,
        S_QRCODE,
        S_SEARCH,

    };

    enum Event
    {
        E_INIT_ERROR,
        E_INIT_SUCCESS,
        E_CONTINUE_BUTTON,
        E_NEW_WAYPOINT,
        E_CLOSE_PROXIMITY,
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
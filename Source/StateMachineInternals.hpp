#ifndef STATEMACHINEINTERNALS_H
#define STATEMACHINEINTERNALS_H

namespace statemachine
{
    void S_INIT_OnEntry();
    void S_SEARCH_OnEntry();
    void S_SETUP_OnEntry();
    void S_WAYPOINT_OnEntry();
    void S_QRCODE_OnEntry();
    void S_HOT_COLD_OnEntry();
    void S_ERROR_OnEntry();
    void S_ENDGAME_OnEntry();

    enum State
    {
        S_NO,
        S_INIT,
        S_QRCODE,
        S_SEARCH,
        S_HOT_COLD,
        S_WAYPOINT,
        S_SETUP,
        S_ENDGAME,
        S_ERROR,

    };

    enum Event
    {
        E_INIT_ERROR,
        E_INIT_SUCCESS,
        E_CONTINUE_BUTTON,
        E_NEW_WAYPOINT,
        E_CLOSE_PROXIMITY,
        E_WAYPOINT_REACHED,
        E_NOT_CLOSE_ANYMORE,
        E_PUZZLE_COMPLETE,
        E_ALL_WAYPOINTS_REACHED,
        E_TURNED_OFF,
        E_NO_ERROR_SOURCE_SET,
        E_ERROR_SENDING_DATA,
        E_ERROR_DURING_GAME,
    };

    struct Transition
    {
        State currentState;
        Event triggerEvent;
        State nextState;
    };

    constexpr Transition transitionTable[] = {
        // Initialization transitions
        {S_INIT, E_INIT_SUCCESS, S_QRCODE},
        {S_INIT, E_INIT_ERROR, S_ERROR},

        // Transitions from QR Code display
        {S_QRCODE, E_CONTINUE_BUTTON, S_SEARCH},

        // Search transitions
        {S_SEARCH, E_CLOSE_PROXIMITY, S_HOT_COLD},
        {S_HOT_COLD, E_NOT_CLOSE_ANYMORE, S_SEARCH},

        // Transitions for finding and interacting with waypoints
        {S_HOT_COLD, E_WAYPOINT_REACHED, S_WAYPOINT},
        {S_WAYPOINT, E_PUZZLE_COMPLETE, S_SETUP},

        // Setup for the next waypoint
        {S_SETUP, E_NEW_WAYPOINT, S_SEARCH},
        {S_SETUP, E_ALL_WAYPOINTS_REACHED, S_ENDGAME},

        // Shutdown
        {S_ERROR, E_TURNED_OFF, S_NO},
        {S_ENDGAME, E_TURNED_OFF, S_NO},

        // Errors during game
        {S_QRCODE, E_ERROR_DURING_GAME, S_ERROR},
        {S_SEARCH, E_ERROR_DURING_GAME, S_ERROR},
        {S_HOT_COLD, E_ERROR_DURING_GAME, S_ERROR},
        {S_WAYPOINT, E_ERROR_DURING_GAME, S_ERROR},
        {S_SETUP, E_ERROR_DURING_GAME, S_ERROR},
        {S_ENDGAME, E_ERROR_SENDING_DATA, S_ERROR},

        // Admin-forced ending or timeouts
        {S_QRCODE, E_FORCE_ENDING_FROM_ADMIN, S_ERROR},
        {S_SEARCH, E_TIME_OUT, S_ERROR},
        {S_HOT_COLD, E_FORCE_ENDING_FROM_ADMIN, S_ERROR},
        {S_WAYPOINT, E_TIME_OUT, S_ERROR},
        {S_SETUP, E_FORCE_ENDING_FROM_ADMIN, S_ERROR},
    };

    struct StateMachine
    {
    public:
        static StateMachine *stateMachineSingelton;
        State currentState = S_NO;
        // TODO create a transition table
        void transition(Event e)
        {
            for (Transition trans : transitionTable)
            {
                if (trans.currentState == currentState && trans.triggerEvent == e)
                {
                    invokeOnEntry(trans.nextState);
                    break;
                }
            }
        }

        /// @brief THIS IS IMPORTANT IF YOU GENERATE EERORS... SET THE ERROR SOURCE FIRST BEFORE TRANSITIONING TO THE ERROR STATE SO THAT THE ERROR STATE KNOWS WHAT CAUSED IT
        /// @param e Error Event
        void setErrorSource(Event e)
        {
            errorSource = e;
        }
        Event getErrorSource(void)
        {
            return errorSource;
        }

    private:
        Event errorSource = E_NO_ERROR_SOURCE_SET;
        void invokeOnEntry(State state)
        {
            switch (state)
            {
            case S_INIT:
                S_INIT_OnEntry();
                break;
            case S_QRCODE:
                S_QRCODE_OnEntry();
                break;
            case S_SEARCH:
                S_SEARCH_OnEntry();
                break;
            case S_HOT_COLD:
                S_HOT_COLD_OnEntry();
                break;
            case S_WAYPOINT:
                S_WAYPOINT_OnEntry();
                break;
            case S_SETUP:
                S_SETUP_OnEntry();
                break;
            case S_ENDGAME:
                S_ENDGAME_OnEntry();
                break;
            case S_ERROR:
                S_ERROR_OnEntry();
                break;
            default:
                break;
            }
        }
    };

}
#endif
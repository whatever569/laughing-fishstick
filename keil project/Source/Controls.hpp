#ifndef CONTROLS_H
#define CONTROLS_H

#define A_BUTTON_SHIFT
#define A_BUTTON_PORT

#define B_BUTTON_SHIFT
#define B_BUTTON_PORT

#define C_BUTTON_SHIFT
#define C_BUTTON_PORT

#define D_BUTTON_SHIFT
#define D_BUTTON_PORT

#define MASK(x) (1UL<<x)

/// @brief the controls class is the class that handles the functionality of user input and is an intermidiary between the game player and internal modules.
class Controls {
    public:
        // at each state, the functions that get called when the control interrupt happens changes... (forexample, at S_QRCODE the function related to button C will be changed to show the next state, while all other functions will be set to execute nothing)
        
        void (* APressedFunction)(void);
        void (* BPressedFunction)(void);
        void (* CPressedFunction)(void);
        void (* DPressedFunction)(void);
        static Controls * controlsSingleton;

        /// @brief Sets the functions for each button, use at the start of each state. These callback functions are executed in an ISR and therefore should be short and handle only time sensitive stuff.
        /// @param A Call back function for the A button
        /// @param B Call back function for the B button
        /// @param C Call back function for the C button
        /// @param D Call back function for the D button
        void setFunctionsForButtons(void (* A)(void), void (* B)(void), void (* C)(void), void (* D)(void))
        {
            APressedFunction = A;
            BPressedFunction = B;
            CPressedFunction = C;
            DPressedFunction = D;
        }

        /// @brief does nothing, for readability
        static void doNothing()
        {
            //nothing is done here, this is only for readablity
        }

};
#endif

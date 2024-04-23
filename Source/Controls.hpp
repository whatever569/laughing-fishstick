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

class Controls {
    public:
        /// @brief at each state, the functions that get called when the control interrupt happens changes... (forexample, at S_QRCODE the function related to button C will be changed to show the next state, while all other functions will be set to execute nothing)
        void (* APressedFunction)(void);
        void (* BPressedFunction)(void);
        void (* CPressedFunction)(void);
        void (* DPressedFunction)(void);
        static Controls * controlsSingleton;
        // bool isAPressed()
        // {
        //     return false;
        // }
        // bool isBPressed()
        // {
        //     return false;
        // }
        // bool isCPressed()
        // {
        //     return false;
        // }
        // bool isDPressed()
        // {
        //     return false;
        // }

        void setFunctionsForButtons(void (* A)(void), void (* B)(void), void (* C)(void), void (* D)(void))
        {
            APressedFunction = A;
            BPressedFunction = B;
            CPressedFunction = C;
            DPressedFunction = D;
        }

        static void doNothing()
        {
            //nothing is done here, this is only for readablity
        }



};
#endif
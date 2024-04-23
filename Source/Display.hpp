//Anna define the "show" functions and dont change their scope

#ifndef DISPLAY_H
#define DISPLAY_H
/// @brief display class handles the display peripheral and shows screens for each state
class Display
{
    public:
    //define all functions to be used as static so they are accessible from the type (no object has to be initialized to access type)
        static void showINITScreen();
        static void showQRCODEScreen();
        static void showSEARCHScreen();
        /// @brief is the screen that shows up when the user presses the show direction button, also implement the function in S_SEARCH.cpp
        static void showDIRECTIONSEARCHscreen();
    private:
    
};
#endif
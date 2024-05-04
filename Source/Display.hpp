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
        /// @brief is the screen that shows up when the user presses the show direction button
        static void showDIRECTIONSEARCHscreen();

        static void showLeftArrow();
        static void showRightArrow();
        static void showUpArrow();
        static void showDownArrow();

        static void showS_HOT_COLDVeryColdStatus();
        static void showS_HOT_COLDColdStatus();
        static void showS_HOT_COLDWarmStatus();
        static void showS_HOT_COLDHotStatus();

        //Implement this optionally to indicate to the user that they strayed away from the waypoint to much and now they have to 
        //search for it again, make sure to update the product report if you made the screen which I think is a good idea
        static void showS_HOT_COLDNotCloseAnymore();

        static void showS_WAYPOINT_SimonSaysPuzzlePrompt();
        static void showS_WAYPOINT_SimonSaysControlsTutorial();
        static void showAwaitingUserInput();
        static void showPuzzleLost();
        static void showPuzzleWon();
        //implement this function to show a screen for n amount of seconds, and then returning to another screen
        static void showScreenForNSeconds(int n, void (*screenToBeShown)(void), void (*screenToReturnTo));
        //show nothing or maybe a "Loading..." screen
        static void showNothingForNow();

        //This screen shows up when the GPS is disconnected, so the user is prompted to find a better spot
        static void showAwaitingReconnection();
        static void showS_ENDGAMEGameEndedBecauseAllWaypointsWereReached();\
        //no reason for the error was given, check transitions to error state
        static void showS_ERROR_NO_SOURCE();
        static void showS_ERROR_ERROR_SENDING_DATA_AT_S_ENDGAME();
        static void showS_ERROR_ERROR_DURING_GAME();
        static void showS_ERROR_ERROR_INIT();
    private:
    
};
#endif
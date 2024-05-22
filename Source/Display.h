// Anna define the "show" functions and dont change their scope

#ifndef DISPLAY_H
#define DISPLAY_H
/// @brief display class handles the display peripheral and shows screens for each state
class Display
{
public:
    // define all functions to be used as static so they are accessible from the type (no object has to be initialized to access type)
    static void showINITScreen(void);
    static void showQRCODEScreen(void);
    static void showSEARCHScreen(void);
    /// @brief is the screen that shows up when the user presses the show direction button
    static void showDIRECTIONSEARCHscreen(void);

    static void showLeftArrow(void);
    static void showRightArrow(void);
    static void showUpArrow(void);
    static void showDownArrow(void);

    static void showS_HOT_COLDVeryColdStatus(void);
    static void showS_HOT_COLDColdStatus(void);
    static void showS_HOT_COLDWarmStatus(void);
    static void showS_HOT_COLDHotStatus(void);

    // Implement this optionally to indicate to the user that they strayed away from the waypoint to much and now they have to
    // search for it again, make sure to update the product report if you made the screen which I think is a good idea
    static void showS_HOT_COLDNotCloseAnymore(void);

    static void showS_WAYPOINT_SimonSaysPuzzlePrompt(void);
    static void showS_WAYPOINT_SimonSaysControlsTutorial(void);
    static void showAwaitingUserInput(void);
    static void showPuzzleLost(void);
    static void showPuzzleWon(void);
    // implement this function to show a screen for n amount of seconds, and then returning to another screen
    static void showScreenForNSeconds(int n, void (*screenToBeShown)(void), void (*screenToReturnTo)(void));
    // "Loading..." screen
    static void showLoading(void);
    // This screen shows up when the GPS is disconnected, so the user is prompted to find a better spot
    static void showAwaitingReconnection(void);
    static void showS_ENDGAMEGameEndedBecauseAllWaypointsWereReached(void);
    // no reason for the error was given, check transitions to error state
    static void showS_ERROR_NO_SOURCE(void);
    static void showS_ERROR_ERROR_SENDING_DATA_AT_S_ENDGAME(void);
    static void showS_ERROR_ERROR_DURING_GAME(void);
    static void showS_ERROR_ERROR_INIT(void);
    // display nothing, I am assuming that whatever functions you will be working on will display the information in a sustained manner until they get removed
    // so this function will be used to clear the display whenever there was a screen before to avoid erronous showings of content
    static void clearScreen(void);

private:
};
#endif

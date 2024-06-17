#ifndef DISPLAY_H
#define DISPLAY_H

#include "ssd1306.h"

/// @brief display class handles the display peripheral and shows screens for each state
class Display 
{
public:
	
    Display();

    // define all functions to be used as static so they are accessible from the type (no object has to be initialized to access type)
    static void displayInit();
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

    static void showS_HOT_COLDNotCloseAnymore();

    static void showS_WAYPOINT_SimonSaysPuzzlePrompt();
    static void showS_WAYPOINT_SimonSaysControlsTutorial();
    static void showAwaitingUserInput();
	static void showNextRound(int round);
    static void showPuzzleLost();
    static void showPuzzleWon();
    // show a screen for n amount of seconds, and then returning to another screen
    static void showScreenForNSeconds(long n, void (*screenToBeShown)(void), void(*screenToReturnTo) (void));
    // "Loading..." screen
    static void showLoading();
	static void showTurnOff();
    // This screen shows up when the GPS is disconnected, so the user is prompted to find a better spot
    static void showAwaitingReconnection();
    static void showS_ENDGAMEGameEndedBecauseAllWaypointsWereReached();
    // no reason for the error was given, check transitions to error state
    static void showS_ERROR_NO_SOURCE();
    static void showS_ERROR_ERROR_SENDING_DATA_AT_S_ENDGAME();
    static void showS_ERROR_ERROR_DURING_GAME();
    static void showS_ERROR_ERROR_INIT();
	
	static void testDistance(double distance, long n, void(*screenToReturnTo) (void)); 

    static void clearScreen();
		
private:
};

extern volatile int showForNSecondsCalledFlag;

// stores the screenToReturnTo that was set in showScreenForNSeconds
extern void (*returnScreen)(void);
	
//stores the amount of milliseconds that screenToBeShown needs to be shown for
extern long nScreenMilliseconds;
	
//stores the milliSecond count at the moment when the showScreenForNSeconds function was called
extern volatile long millisWhenShowForNSecondsCalled;

#endif


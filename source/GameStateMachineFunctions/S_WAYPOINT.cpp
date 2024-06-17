#include <array>
#include "../GameData.h"
#include "../StateMachineInternals.h"
#include "../display/Display.h"
#include "../Controls.h"
#include "../User.h"
#include "../RandomNumberGenerator.h"
#include "../GPSLocation.h"

#define SIMONSAYS_SPEED 500

using namespace std;
using namespace statemachine;
using namespace GameData;

void APressed();
void BPressed();
void CPressed();
void DPressed();

// TODO check if correctly defined
int RNGpinShift = 5; // RNG = Random Number Generator, it uses a dangling non connected pin, just assign these some random pin
GPIO_Type *RNGGPIOModulePort = GPIOA;
PORT_Type *RNGportModulePort = PORTA;
const int RNGBits = 4;
int RNGportShift = 0;

const int showingPuzzlePromptScreenNSeconds = 4;
const int showingControlsForSeconds = 4;

// Simon says specific
int userInputSize = 0; // to keep track of the current size of userInput
const int numberOfRounds = 2;                  // how many rounds of simon says
int arrowsToBeShownSize = 0; // to keep track of the current size of arrowsToBeShown
const int baseNumberOfDirectionsToBeShown = 2; // this is the first amount of direction that will be shown, where a direction is added at each round
const int secondsForTheEachDirectionToBeShown = 1;
array<GPSLocation::Direction, baseNumberOfDirectionsToBeShown + numberOfRounds> arrowsToBeShown; // array holding the sequence, assuming a maximum of 10 directions
array<GPSLocation::Direction, arrowsToBeShown.size()> userInput; // array holding users input, assuming maximum 10 inputs

bool didDirectionsGetShown = false;

struct SimonSaysGame
{
public:
    SimonSaysGame(int rounds)
    {
        numberOfRounds = rounds-1;
        currentRound = 0;
        initDirs();
    }
    
    /// @return true if the puzzle is finished
    bool nextRound()
    {
        if (numberOfRounds == currentRound)
        {
            Controls::controlsSingleton->setFunctionsForButtons(Controls::doNothing, Controls::doNothing, Controls::doNothing, Controls::doNothing);
            return true;
        }
        else
        {
            currentRound++;
			userInputSize = 0;
			Display::showNextRound(currentRound);
			delay_ms(4e3);
            GPSLocation::Direction randDirection = static_cast<GPSLocation::Direction>(rand() % 4);
            directionsToBeShown[directionsToBeShownSize++] = randDirection;
            showArrowSequence();
            return false;
        }
    }

    int getCurrentRound()
    {
        return currentRound;
    }

    int getNumberOfRounds()
    {
        return numberOfRounds;
    }

    array<GPSLocation::Direction, 10> getDirToBeShown()
    {
        return directionsToBeShown;
    }

    int getDirToBeShownSize()
    {
        return directionsToBeShownSize;
    }

    void showArrowSequence()
    {
		Controls::controlsSingleton->setFunctionsForButtons(Controls::doNothing, Controls::doNothing, Controls::doNothing, Controls::doNothing);
		
        for (int i = 0; i < getDirToBeShownSize(); i++)
        {
            GPSLocation::Direction direction = directionsToBeShown[i];
            switch (direction)
            {
            case (GPSLocation::LEFT):
                Display::showLeftArrow();
				delay_ms(SIMONSAYS_SPEED);
                break;
            case (GPSLocation::RIGHT):
                Display::showRightArrow();
				delay_ms(SIMONSAYS_SPEED);
                break;
            case (GPSLocation::UP):
                Display::showUpArrow();
				delay_ms(SIMONSAYS_SPEED);
                break;
            case (GPSLocation::DOWN):
                Display::showDownArrow();
				delay_ms(SIMONSAYS_SPEED);
                break;
            }
			
			Display::clearScreen();
			delay_ms(150);
        }
		
		Display::showAwaitingUserInput();

        Controls::controlsSingleton->setFunctionsForButtons(
            APressed,
            BPressed,
            CPressed,
            DPressed);
    }

private:
    int numberOfRounds;
    int currentRound;
    array<GPSLocation::Direction, 10> directionsToBeShown;
    int directionsToBeShownSize = 0;

    void initDirs()
    {
        directionsToBeShown.fill(GPSLocation::UP); // Initialize with some default value
        for (int i = 0; i < baseNumberOfDirectionsToBeShown; i++)
        {
            GPSLocation::Direction randDirection = static_cast<GPSLocation::Direction>(rand() % 4);
            directionsToBeShown[directionsToBeShownSize++] = randDirection;
        }
    }
};

unique_ptr<SimonSaysGame> simonSaysGame(new SimonSaysGame(numberOfRounds));

void S_WAYPOINT_OnEntry()
{
    Display::clearScreen();
    StateMachine::stateMachineSingelton->currentState = S_WAYPOINT;
	InitGameData::gameDataSingleton->wayPoints[User::userSingleton->currentWayPointNumber].setIsReached(true);

    // to protect the user from doing anything during showing them the game tutorial
    Controls::controlsSingleton->setFunctionsForButtons(Controls::doNothing, Controls::doNothing, Controls::doNothing, Controls::doNothing);

    // check if the puzzle for the current waypoint is simon says
    if (InitGameData::gameDataSingleton->wayPoints[User::userSingleton->currentWayPointNumber].waypointPuzzle == SimonSays)
    {
        // game tutorial
        Display::showS_WAYPOINT_SimonSaysPuzzlePrompt();
        delay_ms(showingPuzzlePromptScreenNSeconds * 1e3);
		
		Display::showS_WAYPOINT_SimonSaysControlsTutorial();
		delay_ms(showingControlsForSeconds * 1e3);
		
		simonSaysGame->showArrowSequence();
    }
}

void buttonForDirectionPressed(GPSLocation::Direction dir)
{
    if (userInputSize < simonSaysGame->getDirToBeShownSize())
    {
        userInput[userInputSize++] = dir;
		Display::clearScreen();
		
		switch (dir) {
			case (GPSLocation::LEFT):
                Display::showLeftArrow();
                break;
            case (GPSLocation::RIGHT):
                Display::showRightArrow();
                break;
            case (GPSLocation::UP):
                Display::showUpArrow();
                break;
            case (GPSLocation::DOWN):
                Display::showDownArrow();
                break;
            }
	
        if (userInputSize == simonSaysGame->getDirToBeShownSize())
        {
            bool success = true;
            for (int i = 0; i < userInputSize; i++)
            {
                if (userInput[i] != simonSaysGame->getDirToBeShown()[i])
                {
                    success = false;
                    break;
                }
            }
            if (success)
            {
                if (simonSaysGame->nextRound())
                {
                    Display::showPuzzleWon();
					delay_ms(3e3);
					
                    InitGameData::gameDataSingleton->wayPoints[User::userSingleton->currentWayPointNumber].setIsPuzzleSuccess(true);
					transitionFlag = true;
					currentEvent = E_PUZZLE_COMPLETE;
                }
            }
            else
            {
                Display::showPuzzleLost();
				delay_ms(3e3);
                InitGameData::gameDataSingleton->wayPoints[User::userSingleton->currentWayPointNumber].setIsPuzzleSuccess(false);
				transitionFlag = true;
				currentEvent = E_PUZZLE_COMPLETE;
            }
        }
    }
}

void APressed()
{
    buttonForDirectionPressed(GPSLocation::UP);
}
void BPressed()
{
    buttonForDirectionPressed(GPSLocation::LEFT);
}
void CPressed()
{
    buttonForDirectionPressed(GPSLocation::RIGHT);
}
void DPressed()
{
    buttonForDirectionPressed(GPSLocation::DOWN);
}

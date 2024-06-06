#include <array>
#include "../GameData.h"
#include "../StateMachineInternals.h"
#include "../display/Display.h"
#include "../Controls.h"
#include "../User.h"
#include "../RandomNumberGenerator.h"
#include "../GPSLocation.h"
using namespace std;
using namespace statemachine;
using namespace GameData;

void APressed();
void BPressed();
void CPressed();
void DPressed();

// TODO Define these plz
int RNGpinShift; // RNG = Random Number Generator, it uses a dangling non connected pin, just assign these some random pin
GPIO_Type *RNGGPIOModulePort;
PORT_Type *RNGportModulePort;
const int RNGBits = 4;
int RNGportShift;

const int showingPuzzlePromptScreenNSeconds = 3;
const int showingControlsForSeconds = 5;


// Simon says specific
int userInputSize = 0; // to keep track of the current size of userInput
const int numberOfRounds = 3;                  // how many rounds of simon says
int arrowsToBeShownSize = 0; // to keep track of the current size of arrowsToBeShown
const int baseNumberOfDirectionsToBeShown = 3; // this is the first amount of direction that will be shown, where a direction is added at each round
const int secondsForTheEachDirectionToBeShown = 1;
array<GPSLocation::Direction, baseNumberOfDirectionsToBeShown + numberOfRounds> arrowsToBeShown; // array holding the sequence, assuming a maximum of 10 directions
array<GPSLocation::Direction, arrowsToBeShown.size()> userInput; // array holding users input, assuming maximum 10 inputs

bool didDirectionsGetShown = false;

struct SimonSaysGame
{
public:
    SimonSaysGame(int rounds)
    {
        numberOfRounds = rounds;
        currentRound = 0;
        initDirs();
    }
    
    /// @return true if the puzzle is finished
    bool nextRound()
    {
        if (numberOfRounds - 1 == currentRound)
        {
            Controls::controlsSingleton->setFunctionsForButtons(Controls::doNothing, Controls::doNothing, Controls::doNothing, Controls::doNothing);
            return true;
        }
        else
        {
            Controls::controlsSingleton->setFunctionsForButtons(Controls::doNothing, Controls::doNothing, Controls::doNothing, Controls::doNothing);
            currentRound++;
            GPSLocation::Direction randDirection = static_cast<GPSLocation::Direction>(generaterandom32bitint(RNGpinShift, RNGportShift, RNGGPIOModulePort, RNGBits, RNGportModulePort) % 4);
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
        for (int i = 0; i < getDirToBeShownSize(); i++)
        {
            GPSLocation::Direction direction = directionsToBeShown[i];
            switch (direction)
            {
            case (GPSLocation::LEFT):
                Display::showScreenForNSeconds(secondsForTheEachDirectionToBeShown, Display::showLeftArrow, Display::clearScreen);
                break;
            case (GPSLocation::RIGHT):
                Display::showScreenForNSeconds(secondsForTheEachDirectionToBeShown, Display::showRightArrow, Display::clearScreen);
                break;
            case (GPSLocation::UP):
                Display::showScreenForNSeconds(secondsForTheEachDirectionToBeShown, Display::showUpArrow, Display::clearScreen);
                break;
            case (GPSLocation::DOWN):
                Display::showScreenForNSeconds(secondsForTheEachDirectionToBeShown, Display::showDownArrow, Display::clearScreen);
                break;
            }
        }

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
            GPSLocation::Direction randDirection = static_cast<GPSLocation::Direction>(generaterandom32bitint(RNGpinShift, RNGportShift, RNGGPIOModulePort, RNGBits, RNGportModulePort) % 4);
            directionsToBeShown[directionsToBeShownSize++] = randDirection;
        }
    }
};

unique_ptr<SimonSaysGame> simonSaysGame(new SimonSaysGame(numberOfRounds));

void S_WAYPOINT_OnEntry()
{
    Display::clearScreen();
    StateMachine::stateMachineSingelton->currentState = S_WAYPOINT;

    // to protect the user from doing anything during showing them the game tutorial
    Controls::controlsSingleton->setFunctionsForButtons(Controls::doNothing, Controls::doNothing, Controls::doNothing, Controls::doNothing);

    // check if the puzzle for the current waypoint is simon says
    if (InitGameData::gameDataSingleton->wayPoints[User::userSingleton->currentWayPointNumber].waypointPuzzle == SimonSays)
    {
        // game tutorial
        Display::showScreenForNSeconds(showingPuzzlePromptScreenNSeconds,
                                       Display::showS_WAYPOINT_SimonSaysPuzzlePrompt,
                                       Display::showLoading);
        Display::showScreenForNSeconds(showingControlsForSeconds,
                                       Display::showS_WAYPOINT_SimonSaysControlsTutorial,
                                       Display::showLoading);
    }
}

void buttonForDirectionPressed(GPSLocation::Direction dir)
{
    if (userInputSize < simonSaysGame->getDirToBeShownSize())
    {
        userInput[userInputSize++] = dir;
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
                    Display::showScreenForNSeconds(3, Display::showPuzzleWon, Display::showLoading);
                    InitGameData::gameDataSingleton->wayPoints[User::userSingleton->currentWayPointNumber].setIsPuzzleSuccess(true);
                    StateMachine::stateMachineSingelton->transition(E_PUZZLE_COMPLETE);
                }
            }
            else
            {
                Display::showScreenForNSeconds(3, Display::showPuzzleLost, Display::showLoading);
                InitGameData::gameDataSingleton->wayPoints[User::userSingleton->currentWayPointNumber].setIsPuzzleSuccess(false);
                StateMachine::stateMachineSingelton->transition(E_PUZZLE_COMPLETE);
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

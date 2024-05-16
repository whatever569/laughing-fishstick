#include <vector>
#include <memory>
#include "../GameData.hpp"
#include "../StateMachineInternals.hpp"
#include "../Display.hpp"
#include "../Controls.hpp"
#include "../User.hpp"
#include "../RandomNumberGenerator.hpp"
using namespace std;
using namespace statemachine;
using namespace GameData;
using namespace randomNG;

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

enum Directions
{
    LEFT,
    UP,
    RIGHT,
    DOWN
};

// Simon says specific
vector<Directions> userInput;                  // vector holding users input
const int numberOfRounds = 3;                  // how many rounds of simon says
vector<Directions> arrowsToBeShown;            // set of arrows to be displayed as the sequence
const int baseNumberOfDirectionsToBeShown = 3; // this is the first amount of direcrtion that will be shown, where a direction is added at each round
const int secondsForTheEachDirectionToBeShown = 1;
bool didDirectionsGetShown = false;
const double interruptFrequency = 1.5;

struct SimonSaysGame
{
public:
    SimonSaysGame(int rounds)
    {
        numberOfRounds = rounds;
        for (int i = 0; i < baseNumberOfDirectionsToBeShown; i++)
        {
            Directions randDirection = static_cast<Directions>(generaterandom32bitint(RNGpinShift, RNGportShift, RNGGPIOModulePort, RNGBits, RNGportModulePort) % 4);
            directionsToBeShown.push_back(randDirection);
        }

        currentRound = 0;
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
            Directions randDirection = static_cast<Directions>(generaterandom32bitint(RNGpinShift, RNGportShift, RNGGPIOModulePort, RNGBits, RNGportModulePort) % 4);
            directionsToBeShown.push_back(randDirection);
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

    vector<Directions> getDirToBeShown()
    {
        return directionsToBeShown;
    }

    void showArrowSequence()
    {
        for (Directions direction : getDirToBeShown())
        {
            switch (direction)
            {
            case (LEFT):
                Display::showScreenForNSeconds(secondsForTheEachDirectionToBeShown, Display::showLeftArrow, Display::clearScreen);
                break;
            case (RIGHT):
                Display::showScreenForNSeconds(secondsForTheEachDirectionToBeShown, Display::showRightArrow, Display::clearScreen);
                break;
            case (UP):
                Display::showScreenForNSeconds(secondsForTheEachDirectionToBeShown, Display::showUpArrow, Display::clearScreen);
                break;
            case (DOWN):
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
    vector<Directions> directionsToBeShown;
};

unique_ptr<SimonSaysGame> simonSaysGame(new SimonSaysGame(numberOfRounds));

void S_WAYPOINT_OnEntry()
{
    Display::clearScreen();
    StateMachine::stateMachineSingelton->currentState = S_WAYPOINT;

    // to protect the user from doing anything during showing them the game tutorial
    Controls::controlsSingleton->setFunctionsForButtons(Controls::doNothing, Controls::doNothing, Controls::doNothing, Controls::doNothing);

    // check if the puzzle for the current waypoint is simon says
    if (InitGameData::gameDataSingleton->wayPoints[User::userSingelton->currentWayPointNumber].waypointPuzzle == SimonSays)
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

void buttonForDirectionPressed(Directions dir)
{
    if (userInput.size() - 1 < simonSaysGame->getDirToBeShown().size())
    {
        userInput.push_back(dir);
    }
    else if (userInput.size() < simonSaysGame->getDirToBeShown().size())
    {
        userInput.push_back(dir);
        if (userInput == simonSaysGame->getDirToBeShown())
        {
            if (simonSaysGame->nextRound())
            {
                Display::showScreenForNSeconds(3, Display::showPuzzleWon, Display::showLoading);
                InitGameData::gameDataSingleton->wayPoints[User::userSingelton->currentWayPointNumber].setIsPuzzleSuccess(true);
                StateMachine::stateMachineSingelton->transition(E_PUZZLE_COMPLETE);
            }
        }
        else
        {
            Display::showScreenForNSeconds(3, Display::showPuzzleLost, Display::showLoading);
            InitGameData::gameDataSingleton->wayPoints[User::userSingelton->currentWayPointNumber].setIsPuzzleSuccess(false);
            StateMachine::stateMachineSingelton->transition(E_PUZZLE_COMPLETE);
        }
    }
}

void APressed()
{
    buttonForDirectionPressed(UP);
}
void BPressed()
{
    buttonForDirectionPressed(LEFT);
}
void CPressed()
{
    buttonForDirectionPressed(RIGHT);
}
void DPressed()
{
    buttonForDirectionPressed(DOWN);
}

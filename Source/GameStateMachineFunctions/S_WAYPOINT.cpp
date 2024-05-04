using namespace std;
using namespace statemachine;
#include <vector>
#include "../GameData.hpp"
#include "../StateMachineInternals.hpp"
#include "../Display.hpp"
#include "../Controls.hpp"
#include "../User.hpp"
#include "../RandomNumberGenerator.hpp"
//TODO Define these plz
const int RNGpinShift;  //RNG = Random Number Generator, it uses a dangling non connected pin, just assign these some random pin
GPIO_Type *RNGport;
const int RNGBits = 4;
const int RNGportShift;

using namespace GameData;
using namespace projectmetadata;
using namespace random;
const int showingPuzzlePromptScreenNSeconds = 3;
const int showingControlsForSeconds = 5;

//Simon says
vector<dirs> userInput;
const int numberOfRounds = 3; //this is how many arrows show up for each round of simon says
vector<dirs> arrowsToBeShown;
const int baseNumberOfDirectionsToBeShown = 3; //this is the first amount of direcrtion that will be shown, where a direction is added at each round
SimonSaysGame *simonSaysGame = new SimonSaysGame(numberOfRounds);
enum dirs
{
    LEFT,
    UP,
    RIGHT,
    DOWN
};

void S_WAYPOINT_OnEntry()
{
    StateMachine::stateMachineSingelton->currentState = S_WAYPOINT;
    // to protect the user from doing anything during showing them the game tutorial
    Controls::controlsSingleton->setFunctionsForButtons(
        Controls::doNothing, Controls::doNothing, Controls::doNothing, Controls::doNothing);
    //check if the puzzle for the current waypoint is simon says, this is because some screens are simon says specific
    if (InitGameData::gameDataSingleton->wayPoints[User::userSingelton->currentWayPointNumber].waypointPuzzle == SimonSays)
    {
            // game tutorial
        Display::showScreenForNSeconds(showingPuzzlePromptScreenNSeconds,
                                        Display::showS_WAYPOINT_SimonSaysPuzzlePrompt, 
                                        Display::showNothingForNow);
        Display::showScreenForNSeconds(showingControlsForSeconds,
                                        Display::showS_WAYPOINT_SimonSaysControlsTutorial,
                                        Display::showNothingForNow);
        
        Controls::controlsSingleton->setFunctionsForButtons(
            APressed,
            BPressed,
            CPressed,
            DPressed
        );

    }
}




/// @brief Function if A is pressed during game (simon says)
void APressed()
{
    if(userInput.size() - 1 < simonSaysGame->getDirToBeShown().size())
    {
        userInput.push_back(UP);
        return;
    }
    else if(userInput.size() < simonSaysGame->getDirToBeShown().size()){
        userInput.push_back(UP);
        if(userInput == simonSaysGame->getDirToBeShown())
        {
            if(simonSaysGame->nextRound())
            {
                Display::showScreenForNSeconds(3, Display::showPuzzleWon, Display::showNothingForNow);
                InitGameData::gameDataSingleton->wayPoints[User::userSingelton->currentWayPointNumber].setIsPuzzleSuccess(true);
                StateMachine::stateMachineSingelton->transition(E_PUZZLE_COMPLETE);
            }
        }else
        {
            Display::showScreenForNSeconds(3, Display::showPuzzleLost, Display::showNothingForNow);
            InitGameData::gameDataSingleton->wayPoints[User::userSingelton->currentWayPointNumber].setIsPuzzleSuccess(false);
            StateMachine::stateMachineSingelton->transition(E_PUZZLE_COMPLETE);
        }
    }
}

//the following functions are identical to APressed
#pragma region 
/// @brief Function if B is pressed during game (simon says)
void BPressed()
{
    if(userInput.size() - 1 < simonSaysGame->getDirToBeShown().size())
    {
        userInput.push_back(LEFT);
        return;
    }
    else if(userInput.size() < simonSaysGame->getDirToBeShown().size()){
        userInput.push_back(LEFT);
        if(userInput == simonSaysGame->getDirToBeShown())
        {
            if(simonSaysGame->nextRound())
            {
                Display::showScreenForNSeconds(3, Display::showPuzzleWon, Display::showNothingForNow);
                InitGameData::gameDataSingleton->wayPoints[User::userSingelton->currentWayPointNumber].setIsPuzzleSuccess(true);
                StateMachine::stateMachineSingelton->transition(E_PUZZLE_COMPLETE);
            }
        }else
        {
            Display::showScreenForNSeconds(3, Display::showPuzzleLost, Display::showNothingForNow);
            InitGameData::gameDataSingleton->wayPoints[User::userSingelton->currentWayPointNumber].setIsPuzzleSuccess(false);
            StateMachine::stateMachineSingelton->transition(E_PUZZLE_COMPLETE);
        }
    }
}
/// @brief Function if C is pressed during game (simon says)
void CPressed()
{
    if(userInput.size() - 1 < simonSaysGame->getDirToBeShown().size())
    {
        userInput.push_back(RIGHT);
        return;
    }
    else if(userInput.size() < simonSaysGame->getDirToBeShown().size()){
        userInput.push_back(RIGHT);
        if(userInput == simonSaysGame->getDirToBeShown())
        {
            if(simonSaysGame->nextRound())
            {
                Display::showScreenForNSeconds(3, Display::showPuzzleWon, Display::showNothingForNow);
                InitGameData::gameDataSingleton->wayPoints[User::userSingelton->currentWayPointNumber].setIsPuzzleSuccess(true);
                StateMachine::stateMachineSingelton->transition(E_PUZZLE_COMPLETE);
            }
        }else
        {
            Display::showScreenForNSeconds(3, Display::showPuzzleLost, Display::showNothingForNow);
            InitGameData::gameDataSingleton->wayPoints[User::userSingelton->currentWayPointNumber].setIsPuzzleSuccess(false);
            StateMachine::stateMachineSingelton->transition(E_PUZZLE_COMPLETE);
        }
    }
}
/// @brief Function if D is pressed during game (simon says)
void DPressed()
{
    if(userInput.size() - 1 < simonSaysGame->getDirToBeShown().size())
    {
        userInput.push_back(DOWN);
        return;
    }
    else if(userInput.size() < simonSaysGame->getDirToBeShown().size()){
        userInput.push_back(DOWN);
        if(userInput == simonSaysGame->getDirToBeShown())
        {
            if(simonSaysGame->nextRound())
            {
                Display::showScreenForNSeconds(3, Display::showPuzzleWon, Display::showNothingForNow);
                InitGameData::gameDataSingleton->wayPoints[User::userSingelton->currentWayPointNumber].setIsPuzzleSuccess(true);
                StateMachine::stateMachineSingelton->transition(E_PUZZLE_COMPLETE);
            }
        }else
        {
            Display::showScreenForNSeconds(3, Display::showPuzzleLost, Display::showNothingForNow);
            InitGameData::gameDataSingleton->wayPoints[User::userSingelton->currentWayPointNumber].setIsPuzzleSuccess(false);
            StateMachine::stateMachineSingelton->transition(E_PUZZLE_COMPLETE);
        }
    }
}
#pragma endregion
struct SimonSaysGame
{
    public:

     SimonSaysGame(int rounds)
     {
        numberOfRounds = rounds;
        for(int i = 0; i < baseNumberOfDirectionsToBeShown; i++)
        {
            dirs randDirection = static_cast<dirs>(generaterandom32bitint(RNGpinShift, RNGportShift, RNGport, RNGBits) % 4);
            directionsToBeShown.push_back(randDirection);
        }

        currentRound = 0;
    
     }
    
    /// @brief -
    /// @return returns true if the game is finished
    bool nextRound()
    {
        if (numberOfRounds - 1 == currentRound)
        {
            return true;
        }
        else
        {
            currentRound++;
            dirs randDirection = static_cast<dirs>(generaterandom32bitint(RNGpinShift, RNGportShift, RNGport, RNGBits) % 4);
            directionsToBeShown.push_back(randDirection);
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

    vector<dirs> getDirToBeShown()
    {
        return directionsToBeShown;
    }

     private:
         int numberOfRounds;
         int currentRound;
         vector<dirs> directionsToBeShown;

};

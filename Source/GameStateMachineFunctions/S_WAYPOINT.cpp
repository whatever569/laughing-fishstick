using namespace std;
using namespace statemachine;
#include <vector>
#include "../GameData.hpp"
#include "../StateMachineInternals.hpp"
#include "../Display.hpp"
#include "../Controls.hpp"
#include "../User.hpp"
using namespace GameData;
using namespace projectmetadata;
const int showingPuzzlePromptScreenNSeconds = 3;
const int showingControlsForSeconds = 5;
//Simon says
vector<dirs> userInput;
int gameRound = 0;
const int numberOfRounds = 3; //this is how many arrows show up for each round of simon says
vector<dirs> arrowsToBeShown;

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
    if (InitGameData::gameDataSingleton->wayPoints[User::userSingelton->currentWayPointNumber].getPuzzle() == SimonSays)
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
    if(userInput.size() - 1 < numberOfCombinationsForEachRRound[gameRound])
    {
        userInput.push_back(UP);
        return;
    }
    else if(userInput.size() < numberOfCombinationsForEachRRound[gameRound]){
        userInput.push_back(UP);
        if(userInput == arrowsToBeShown)
        {

        }
    }
}

/// @brief Function if B is pressed during game (simon says)
void BPressed()
{
    if(userInput.size() < numberOfCombinationsForEachRRound[gameRound])
    {
        userInput.push_back(LEFT);
    }
    else
    {

    }
}
/// @brief Function if C is pressed during game (simon says)
void CPressed()
{
    if(userInput.size() < numberOfCombinationsForEachRRound[gameRound])
    {
        userInput.push_back(RIGHT);
    }
}
/// @brief Function if D is pressed during game (simon says)
void DPressed()
{
    if(userInput.size() < numberOfCombinationsForEachRRound[gameRound])
    {
        userInput.push_back(DOWN);
    }
    else
    {
    }
}
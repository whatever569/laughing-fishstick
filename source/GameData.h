#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <string>
#include "GPSLocation.h"
//#include "Controls.h"
#include "User.h"

namespace GameData
{
    const int MAX_WAYPOINTS  =10;
    using namespace std;

    enum Puzzle
    {
      	SimonSays, 		// the user is shown a set of arrows for three rounds, the user has to input back the directions in a set time, for now it is 3 seconds (the timer gets renewed each time the user gives an input)
		TotalPuzzles, 	// This is for safety, if a wrong puzzle number is entered it receives 
	};

    /**
     * @brief this is the basic data type for a waypoint
     * @note use the constructor to make a waypoint object
     */
    struct WayPoint
    {
    private:
        GPSLocation waypointLocation;
        bool isReached = false;
        bool isPuzzleSuccess = false;

    public:
        Puzzle waypointPuzzle;
	
        void setWayPoint(GPSLocation coord, Puzzle puzzle)
        {
			waypointLocation.setCoordinates(coord.getLatitude(), coord.getLongitude());
            waypointPuzzle = puzzle;
        }

        GPSLocation getLocation()
        {
            return waypointLocation;
        }

        void setLocation(GPSLocation location)
        {
			waypointLocation.setCoordinates(location.getLatitude(), location.getLongitude());
        }

        bool getIsReached()
        {
            return isReached;
        }
        void setIsReached(bool didReach)
        {
            isReached = didReach;
        }
        void setIsPuzzleSuccess(bool p)
        {
            isPuzzleSuccess = p;
        }

        bool getIsPuzzleSuccess()
        {
            return isPuzzleSuccess;
        }
    };

    /**
     * @brief This holds all the information concerning the game initial data obtained from admin
     */
    struct InitGameData
    {
        char userName[MAX_NAME_SIZE];
        WayPoint wayPoints[MAX_WAYPOINTS];
        static InitGameData* gameDataSingleton;
    };

    struct ScoreData
    {
        static int timesDButtonPressed;
    };
}

#endif

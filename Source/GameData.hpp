#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <string>
#include <vector>
#include "GPSLocation.hpp"
#include "Controls.hpp"
namespace GameData
{
    using namespace std;

    enum Puzzles
    {
        SimonSays, // the user is shown a set of arrows for three rounds, the user has to input back the directions in a set time, for now it is 3 seconds (the timer gets renewed each time the user gives an input)
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
        Puzzles waypointPuzzle;
        WayPoint(GPSLocation coord, Puzzles puzzle)
        {
            waypointLocation.setLatitude(coord.getLatitude());
            waypointLocation.setLongitude(coord.getLongitude());

            waypointPuzzle = puzzle;
        }

        GPSLocation getLocation()
        {
            return waypointLocation;
        }

        void setLocation(GPSLocation location)
        {
            waypointLocation.setLatitude(location.getLatitude());
            waypointLocation.setLongitude(location.getLongitude());
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
        string userName;
        vector<WayPoint> wayPoints;
        static InitGameData *gameDataSingleton;
        InitGameData(string uName, const vector<WayPoint> &wp) : userName(uName), wayPoints(wp) {}
    };
}

#endif
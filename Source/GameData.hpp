#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <string>
#include <vector>
#include "GPSLocation.hpp"

namespace GameData {
    using namespace std;

    enum Puzzles {
        gyroscope,
    };

    /**
     * @brief this is the basic data type for a waypoint
     * @note use the constructor to make a waypoint object
    */
    struct WayPoint {
        private:
        GPSLocation waypointLocation;
        Puzzles waypointPuzzle;
        bool isReached = false;
        public:
        WayPoint(GPSLocation coord, Puzzles puzzle){
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
    };

    /**
     * @brief This holds all the information concerning the game initial data obtained from admin
    */
    struct InitGameData {
		static InitGameData* gameDataSingleton;
        string userName;
        vector<WayPoint> wayPoints;
        InitGameData(string uName, const vector<WayPoint>& wp) : userName(uName), wayPoints(wp) {}
    };
}


#endif
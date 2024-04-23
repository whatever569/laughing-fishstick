#ifndef USER_H
#define USER_H
#include <string>
#include <GPSLocation.hpp>
using namespace std;

/// @brief This represents the current user that is playing the game rn, remember to initialize the userSingelton object at S_INIT
class User
{
    public:
        static User* userSingelton;
        string username = "Unassigned at intialization";
        int timeDirectionButtonPressed;
        int currentWayPointNumber;
    GPSLocation getUsersCurrentLocation()
    {
        GPSLocation currentLocation {GPSLocation()};
        //Todo
        return currentLocation;
    }
};
#endif
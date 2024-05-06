#ifndef USER_H
#define USER_H
#include <string>
#include "GPSLocation.hpp"
using namespace std;

#define MAX_NAME_SIZE 16

/// @brief This represents the current user that is playing the game rn, remember to initialize the userSingelton object at S_INIT
class User
{
public:
    static User *userSingelton;
    char* username[16];
    int timeDirectionButtonPressed = 0;
    int currentWayPointNumber = 0;

    GPSLocation getUsersCurrentLocation()
    {
        GPSLocation currentLocation{GPSLocation()};
        // Todo
        return currentLocation;
    }
};
#endif
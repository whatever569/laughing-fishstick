#ifndef USER_H
#define USER_H

#include "GPSLocation.h"

#define MAX_NAME_SIZE 16

/// @brief This represents the current user that is playing the game rn, remember to initialize the userSingleton object at S_INIT
struct User
{
public:
    static User* userSingleton;
    char username[16];
    int timeDirectionButtonPressed = 0;
    int currentWayPointNumber = 0;
	int TotalWayPoints = 0;

	void setUsersCurrentLocation(char* coordinates);	
    GPSLocation getUsersCurrentLocation(void);
	
	private:
		GPSLocation currentLocation;
};
#endif
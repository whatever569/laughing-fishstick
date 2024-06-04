#ifndef USER_H
#define USER_H
#include "GPSLocation.h"
#include "GPS/GPS.h"
#include <string.h>

#define MAX_NAME_SIZE 16

/// @brief This represents the current user that is playing the game rn, remember to initialize the userSingleton object at S_INIT
class User
{
public:
    static User* userSingleton;
    char username[16];
    int timeDirectionButtonPressed = 0;
    int currentWayPointNumber = 0;

    GPSLocation getUsersCurrentLocation()
    {
		GPSLocation currentLocation{GPSLocation()};;
		char coordinates[30] = {0};
		gps(coordinates);
		
		if (coordinates[0] > '9') { 				//if its a letter/not a number, dont set it as location
			char *slon = strchr(coordinates, ',');	//find where lon starts
			double lon = strtod(&slon[2], NULL);	//from position 3 the numbers start, so from that point on write as double
			coordinates[slon-coordinates] = '\0';	//put terminator on the comma 
			double lat = strtod(coordinates, NULL); //write as double
			currentLocation.setCoordinates(lat, lon);
			currentLocation.setIsConnected(true);
		}
		
		else currentLocation.setIsConnected(false);
		
        return currentLocation;
    }
};
#endif
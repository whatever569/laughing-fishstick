#include "User.h"
#include "GPS/GPS.h"
#include <string.h>
#include <ctype.h>

void User::setUsersCurrentLocation(char* coordinates) {	
	gps(coordinates);
	
	if (isdigit(coordinates[0])) { 				//if its a letter/not a number, dont set it as location
		char coordBackup[30] = {0};
		strcpy(coordBackup, coordinates);		//make a backup of coordinates so i dont have to change it
		
		char *slon = strchr(coordinates, ',');	//find where lon starts
		double lon = strtod(&slon[2], NULL);	//from position 3 the numbers start, so from that point on write as double
		coordinates[slon - coordinates] = '\0';	//put terminator on the comma 
		double lat = strtod(coordinates, NULL); //write as double
		
		currentLocation.setCoordinates(lat, lon);
		currentLocation.setIsConnected(true);
	}
	
	else currentLocation.setIsConnected(false);
}

GPSLocation User::getUsersCurrentLocation()
{
	return currentLocation;
}
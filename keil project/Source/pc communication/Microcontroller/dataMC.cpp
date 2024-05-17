#include <string>
#include <stdlib.h>
#include "dataMC.hpp"
#include "uart0.h"
#include "../../User.hpp"
#include "../../GameData.hpp"
#include "../../GPSLocation.hpp"

using namespace GameData;
User* User::userSingleton = nullptr;
InitGameData* InitGameData::gameDataSingleton = nullptr;

void GameDataInit(void) {
	char nameSize[3] = {0};								//Limits name to 99 size, but name is limited to 16 in User.hpp anyway.
	uart0_get_string(nameSize, 2);
	uart0_get_string(User::userSingleton->username, strtol(nameSize, NULL, 10));
	
	InitGameData::gameDataSingleton->userName = User::userSingleton->username;
	
	//get_char - 48, because '0' = 48. EXAMPLE: if get_char = '3' -> 51 as int, 51-48 = 3. 
	int waypointAmount = (int)(uart0_get_char() - 48);			//Limits waypointAmount to 9	
	InitGameData::gameDataSingleton->wayPoints.resize(waypointAmount);
	
	for (int i = 0; i < waypointAmount; i++) {
		//if the Puzzle is accidentally bigger then the amount of Puzzles, it switches around.
		Puzzle waypointPuzzle = (Puzzle)((uart0_get_char() - 48) % TotalPuzzles);	
		
		char lat[10] = {0}, lon[10] = {0};
		uart0_get_string(lat, 10);
		uart0_get_string(lon, 10);
	
		GPSLocation coordinates = GPSLocation(strtod(lat, NULL), strtod(lon, NULL));
		InitGameData::gameDataSingleton->wayPoints[i].setWayPoint(coordinates, waypointPuzzle); 

	}
}

void GameDataCleanup(void) {
    /*
	if (User::userSingleton) {
        delete User::userSingleton;
        User::userSingleton = nullptr;
    }
	
    if (InitGameData::gameDataSingleton) {
        delete InitGameData::gameDataSingleton;
        InitGameData::gameDataSingleton = nullptr;
    }
	*/
}

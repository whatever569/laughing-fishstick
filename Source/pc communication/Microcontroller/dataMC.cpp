#include <string>
#include "dataMC.h"
#include "uart0.h"
#include "../../delay.h"
#include "../../User.h"
#include "../../GameData.h"
#include "../../GPSLocation.h"

using namespace GameData;
User* User::userSingleton = nullptr;
InitGameData* InitGameData::gameDataSingleton = nullptr;

bool GameDataInit(void) {
	while(uart0_num_rx_chars_available() < 10 || milliSecond > 1e4); //wait for data or timeout after 10 seconds
	if (milliSecond > 1e4) return false;
	delay_ms(100);													 //wait a little so all info can get received
	
	char nameSize[3] = {0};											 //Limits name to 99 size, but name is limited to 16 in User.hpp anyway.
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
	
	return true;
}

void GameDataReturn() {

}


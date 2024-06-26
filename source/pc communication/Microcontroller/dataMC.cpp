#include <string.h>
#include "dataMC.h"
#include "uart0.h"
#include "../../delay.h"
#include "../../User.h"
#include "../../GameData.h"
#include "../../GPSLocation.h"
#include "../eeprom/at24c256.h"

using namespace GameData;
using namespace std;

bool GameDataInit(void) {
	uart0_put_char('S');											 //Send start signal
	
	while(uart0_num_rx_chars_available() < 10 && milliSecond < GAMEDATAINIT_TIMEOUT); //wait for data or timeout after 100 seconds
	if (milliSecond >= GAMEDATAINIT_TIMEOUT) return false;
	delay_ms(100);													 //wait a little so all info can get received
	
	char nameSize[3] = {0};											 //Limits name to 99 size, but name is limited to 16 in User.hpp anyway.
	uart0_get_string(nameSize, 2);
	uart0_get_string(User::userSingleton->username, strtol(nameSize, NULL, 10));
	
	strcpy(InitGameData::gameDataSingleton->userName, User::userSingleton->username);
	//get_char - 48, because '0' = 48. EXAMPLE: if get_char = '3' -> 51 as int, 51-48 = 3. 
	User::userSingleton->TotalWayPoints = (int)(uart0_get_char() - 48);			//Limits waypointAmount to 9
	
	for (int i = 0; i < User::userSingleton->TotalWayPoints; i++) {
		//if the Puzzle is accidentally bigger then the amount of Puzzles, it switches around.
		Puzzle waypointPuzzle = (Puzzle)((uart0_get_char() - '0') % TotalPuzzles);	
		
		int coordSize = (int)(uart0_get_char() - '0');
		char lat[10] = {0}, lon[10] = {0};
		uart0_get_string(lat, coordSize);
		uart0_get_string(lon, coordSize);
	
		GPSLocation coordinates = GPSLocation(strtod(lat, NULL), strtod(lon, NULL));
		InitGameData::gameDataSingleton->wayPoints[i].setWayPoint(coordinates, waypointPuzzle); 
	}
	
	return true;
}

void GameDataDefault(void) {
	strcpy(User::userSingleton->username, "DEFAULT_NAME");
	strcpy(InitGameData::gameDataSingleton->userName, User::userSingleton->username);
	//get_char - 48, because '0' = 48. EXAMPLE: if get_char = '3' -> 51 as int, 51-48 = 3. 
	User::userSingleton->TotalWayPoints = 2;
	//if the Puzzle is accidentally bigger then the amount of Puzzles, it switches around.
	Puzzle waypointPuzzle = (Puzzle)0;
	GPSLocation coordinates = GPSLocation(51.989930, 5.949069);
	InitGameData::gameDataSingleton->wayPoints[0].setWayPoint(coordinates, waypointPuzzle); 
	coordinates.setCoordinates(51.988468, 5.949274);
	InitGameData::gameDataSingleton->wayPoints[1].setWayPoint(coordinates, waypointPuzzle); 
}

int GameDataReturn() {
	while(!uart0_num_rx_chars_available());
	uart0_get_char();
	
	int EEPROM_readAdress = 0x0000;
	long startTime = milliSecond;
	
	while (EEPROM_currentAdress > EEPROM_readAdress) {
		char tempData[32] = {0};
		eeprom_read((const int)EEPROM_readAdress, (uint8_t *)tempData, sizeof(tempData));
		EEPROM_readAdress += strlen(tempData) + 1;
		uart0_send_string(tempData);
		delay_ms(50);
		
		if (milliSecond - startTime >= GAMEDATARETURN_TIMEOUT) {
			char timeoutStr[26] = "Timeout of GameDataReturn";
			uart0_send_string(timeoutStr);
			delay_ms(50);
			break;
		}
	}
	
	uart0_put_char(';');
	//while (uart0_num_rx_chars_available());
	//return (int)(uart0_get_char()-'0');		 //when done send from pc 1 if it went correct 0 if it didnt so it doesnt flush eeprom.
	return 1;
}


#include <string>
#include "dataPC.hpp"
#include "pc_uart.hpp"

using namespace GameData;

void gameDataInit (string userName, vector<waypoint> waypoints) {
	PC_UART pc;
	QbyteArray gameData;
	
	gameData.append(userName.size());
	if (userName.size() < 10) gameData.prepend('0');
	gameData.append(userName);
	gameData.append(waypoints.size());
	
	for (int i = 0; i < waypoints.size(); i++) {
		
		gameData.append((char)waypoints[i].waypointPuzzle + 48);
		gameData.append(std::to_string(waypoints[i].GPSLocation.getLatitude()));
		gameData.append(std::to_string(waypoints[i].GPSLocation.getLongitude()));
	}
	
	pc.flush('T');
	pc.transmitData(gameData);
}

Loggingwaypoint GameDataReturn(void) {
	PC_UART pc;
	Q
	
}
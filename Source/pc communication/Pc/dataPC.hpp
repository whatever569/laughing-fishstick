#ifndef DATAPC_HPP
#define DATAPC_HPP

//for using waypoint struct, alternativly could create new struct type here which is simplified version
//this is so that MC code and PC code dont get mixed.
#include "../../GameData.hpp" 
#include "Loggingwaypoint.hpp"

void gameDataInit (string userName, vector<waypoint> waypoints);	//takes data from pc uart to setup game
Loggingwaypoint GameDataReturn(void);								//sends data to pc for stats, temprature and such

#endif
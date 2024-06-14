#ifndef DATAPC_H
#define DATAPC_H

//for using waypoint struct, alternativly could create new struct type here which is simplified version
//this is so that MC code and PC code dont get mixed.
#include <string>
#include <vector>
#include <QSerialPort>
#include "../../../laughing-fishstick/source/GameData.h"
#include "logdata.h"
#include "loggingwaypoint.h"

using namespace std;
bool gameDataInit (string userName, vector<GameData::WayPoint> waypoints);	//takes data from pc uart to setup game
LogData GameDataReturn(void); //sends data to pc for stats, temprature and such
bool IsConnectedToMc (void);
string writeUntil(QByteArray& str, const char* end);
string writeUntil(QByteArray& str, const char end);
string writeUntil(QByteArray& str);

#endif

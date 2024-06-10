#include <string>
#include "datapc.h"
#include "pc_uart.h"
//#include "loggingwaypoint.h"

using namespace GameData;
using namespace std;

bool IsConnectedToMc (void) {
    if (QSerialPortInfo::availablePorts().size()) {
        return true;
    }
    return false;
}

void gameDataInit (string userName, vector<WayPoint> waypoints) {
    PC_UART pc;
    QByteArray gameData;

    while(1) {                  //poll until it receives start info
        QByteArray temp;
        temp = pc.receiveData();
        if (temp.size()) break;
    }

    gameData.append(to_string(userName.size()));
    if (userName.size() < 10) gameData.prepend('0');
    gameData.append(userName);
    gameData.append(to_string(waypoints.size()));

    for (int i = 0; i < (int)waypoints.size(); i++) {

        gameData.append((char)waypoints[i].waypointPuzzle + 48);
        GPSLocation gps = waypoints[i].getLocation();
        gameData.append((int)to_string(gps.getLatitude()).size()+'0');
        gameData.append(to_string(gps.getLatitude()));
        gameData.append(to_string(gps.getLongitude()));
    }

    pc.flush('T');
    pc.transmitData(gameData);
}

LogData GameDataReturn(void) {
    PC_UART pc;
    QByteArray dataArray;
    LogData returnData;

    while(1) {
        QByteArray temp;
        temp = pc.receiveData();
        if (temp.size()) break;
    }

    if (dataArray.size()) {
        returnData.userName = writeUntil(dataArray, "W:");
        returnData.gameWaypoints.resize(stoi(writeUntil(dataArray)));
    }
    int waypointNumber = 0;

    while (dataArray.size()) {
        switch(dataArray[0]) {
        case 'W':
            dataArray.remove(0, 2);
            waypointNumber = stoi(writeUntil(dataArray, 'R'));
            returnData.gameWaypoints[waypointNumber].setIsReached(stoi(writeUntil(dataArray, 'P')));
            returnData.gameWaypoints[waypointNumber].setIsPuzzleComplete(stoi(writeUntil(dataArray, 'T')));
            //returnData.gameWaypoints[waypointNumber].setTimeReachedAfterTheStartOfTheGame(writeUntil(dataArray));
            break;

        case 'D':
            dataArray.remove(0, 1);
            returnData.recordedLocations.resize(returnData.recordedLocations.size() + 1);
            returnData.recordedLocations[returnData.recordedLocations.size()-1].setLat((stof(writeUntil(dataArray, ", "))));
            returnData.recordedLocations[returnData.recordedLocations.size()-1].setLon((stof(writeUntil(dataArray, 'C'))));
            returnData.recordedTemperatures.push_back(stof(writeUntil(dataArray)));
            break;

        case 'E':
            dataArray.remove(0, 1);
            returnData.totalTime = stof(writeUntil(dataArray, 'B'));
            returnData.totalTimesDWasPressed = stoi(writeUntil(dataArray));
            break;

        default:
            dataArray.remove(0, 1);
            break;
        }
    }

    return returnData;
}

string writeUntil(QByteArray& str, const char* end) {
    string returnString;
    string inputString = str.toStdString();
    size_t position = inputString.find(end);

    if (position != string::npos) {
        returnString = inputString.substr(0, position);    // take the substring from the beginning to the end
        str.remove(0, position + strlen(end));               // Remove the substring from the original str
    }

    return returnString;
}

string writeUntil(QByteArray& str, const char end) {
    string returnString;
    string inputString = str.toStdString();
    size_t position = inputString.find(end);

    if (position != string::npos) {
        returnString = inputString.substr(0, position);     // take the substring from the beginning to the end
        str.remove(0, position+1);                          // Remove the substring from the original str
    }

    return returnString;
}

string writeUntil(QByteArray& str) {
    string returnString;
    string inputString = str.toStdString();
    size_t position = inputString.find('|');

    if (position != string::npos) {
        returnString = inputString.substr(0, position);  // take the substring from the beginning to the end
        str.remove(0, position+1);                       // Remove the substring from the original str
    }

    return returnString;
}

#ifndef LOGDATA_H
#define LOGDATA_H
#include "QtCore/qstring.h"
#include "appwaypoint.h"
#include "loggingwaypoint.h"
#include <vector>
using namespace std;
class LogData
{
public:
    LogData();
    ~LogData();

    LogData(const LogData& other);

    LogData& operator=(const LogData& other);

    bool operator==(const LogData& other) const;

    string getUserName() const;
    vector<APPGPSLocation> getRecordedLocations() const;
    vector<LoggingWaypoint> getGameWaypoints() const;
    float getTotalTime() const;
    vector<float> getRecordedTemperatures() const;
    int getTotalTimesDWasPressed();

    void setUserName(const string& userName);
    void setRecordedLocations(const vector<APPGPSLocation>& recordedLocations);
    void setGameWaypoints(const vector<LoggingWaypoint>& gameWaypoints);
    void setTotalTime(float totalTime);
    void setRecordedTemperatures(const vector<float>& recordedTemperatures);
    void setTotalTimesDWasPressed(int times);
    float calculateUserScore(); //this is shown too ofcourse
    float calculateDistanceWalked(); //this is shown
    float calculateDistanceBetweenWaypoints();
    float calculateDistanceBetweenTwoGPSLocations(APPGPSLocation & first, APPGPSLocation & other);

    string userName;
    vector<APPGPSLocation> recordedLocations; //to be displayed on the map
    vector<LoggingWaypoint> gameWaypoints; //to be displayed on the map
    float totalTime; //to be displayed
    vector<float> recordedTemperatures; //to be displayed on a graph in the detail screen, recorded each 20 seconds
    int totalTimesDWasPressed; //shown in the detail screen
    const int timeBetweenEachTempRecording = 15;
    const int timeBetweenEachGPSRecording = 15;
    const int scoreForEachWaypointReached = 250;
    const int bonusForReachingAllWaypoints = 1000;
    const int deductionForExtraKilometersTraveled = 30;
    const int avgWalkingTimePerKilometer = 12; //minutes
    const int deductionForEachExtraMinuteTaken = 6;
    const int deductionForEachDButtonPress = 25;
    QString scoreCalculationString;
};

#endif // LOGDATA_H

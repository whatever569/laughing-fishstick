#include "logdata.h"

LogData::LogData() : totalTime(0.0f), userName(),
    recordedLocations(vector<APPGPSLocation>()),
    recordedTemperatures(vector<float>()),
    gameWaypoints(vector<LoggingWaypoint>()), totalTimesDWasPressed(0)
{}

// Destructor
LogData::~LogData() {}

// Copy constructor
LogData::LogData(const LogData& other)
    : userName(other.userName),
    recordedLocations(other.recordedLocations),
    gameWaypoints(other.gameWaypoints),
    totalTime(other.totalTime),
    recordedTemperatures(other.recordedTemperatures) {}

// Copy assignment operator
LogData& LogData::operator=(const LogData& other) {
    if (this != &other) {
        userName = other.userName;
        recordedLocations = other.recordedLocations;
        gameWaypoints = other.gameWaypoints;
        totalTime = other.totalTime;
        recordedTemperatures = other.recordedTemperatures;
    }
    return *this;
}

// Equality check operator
bool LogData::operator==(const LogData& other) const {
    return userName == other.userName &&
           recordedLocations == other.recordedLocations &&
           gameWaypoints == other.gameWaypoints &&
           totalTime == other.totalTime &&
           recordedTemperatures == other.recordedTemperatures;
}

// Getters
string LogData::getUserName() const {
    return userName;
}

vector<APPGPSLocation> LogData::getRecordedLocations() const {
    return recordedLocations;
}

vector<LoggingWaypoint> LogData::getGameWaypoints() const {
    return gameWaypoints;
}

float LogData::getTotalTime() const {
    return totalTime;
}

vector<float> LogData::getRecordedTemperatures() const {
    return recordedTemperatures;
}

void LogData::setUserName(const string& userName) {
    this->userName = userName;
}

void LogData::setRecordedLocations(const vector<APPGPSLocation>& recordedLocations) {
    this->recordedLocations = recordedLocations;
}

void LogData::setGameWaypoints(const vector<LoggingWaypoint>& gameWaypoints) {
    this->gameWaypoints = gameWaypoints;
}

void LogData::setTotalTime(float totalTime) {
    this->totalTime = totalTime;
}

void LogData::setRecordedTemperatures(const vector<float>& recordedTemperatures) {
    this->recordedTemperatures = recordedTemperatures;
}

int LogData::getTotalTimesDWasPressed()
{
    return totalTimesDWasPressed;
}

void LogData::setTotalTimesDWasPressed(int times)
{
    totalTimesDWasPressed = times;
}

float LogData::calculateUserScore()
{
    return 50.0;
}

#include "logdata.h"
#include <cmath>
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
    vector<LoggingWaypoint> twps;

    for(LoggingWaypoint &wp : getGameWaypoints())
    {
        if(wp.getIsReached())
        {
            twps.push_back(wp);
        }
    }

    int W = twps.size();
    int TOTALW = getGameWaypoints().size();
    float AD = calculateDistanceBetweenWaypoints();
    float D = calculateDistanceWalked();
    float T = getTotalTime() / 60 ; // to mins
    int DBP = getTotalTimesDWasPressed();

    float PW = scoreForEachWaypointReached;
    float BONUS = bonusForReachingAllWaypoints;
    float dPK = deductionForExtraKilometersTraveled;
    float tPK = avgWalkingTimePerKilometer;
    float dPM = deductionForEachExtraMinuteTaken;
    float dDBP = deductionForEachDButtonPress;

    float score = (PW * W) + ((W / (float)TOTALW) * BONUS) -
                  ((D - AD) * dPK) - ((T - (AD * tPK)) * dPM) - (DBP * dDBP);

    QString scoreCalculationString = QString("Score Calculation:\n"
                                             "Waypoints reached (W): %1\n"
                                             "Total waypoints (TOTALW): %2\n"
                                             "Points per waypoint (PW): %3\n"
                                             "Direct distance between waypoints (AD): %4 km\n"
                                             "Total distance traveled (D): %5 km\n"
                                             "Deduction per extra kilometer (dPK): %6\n"
                                             "Time taken (T): %7 minutes\n"
                                             "Avg. time per kilometer (tPK): %8 minutes/km\n"
                                             "Deduction per extra minute (dPM): %9\n"
                                             "Times direction button pressed (DBP): %10\n"
                                             "Deduction per button press (dDBP): %11\n"
                                             "Bonus for reaching all waypoints (BONUS): %12\n\n"
                                             "Formula:\n"
                                             "S = (W * PW) + ((W / TOTALW) * BONUS) - ((D - AD) * dPK) - ((T - (AD * tPK)) * dPM) - (DBP * dDBP)\n\n"
                                             "Calculated Score: %13")
                                         .arg(W)
                                         .arg(TOTALW)
                                         .arg(PW)
                                         .arg(AD)
                                         .arg(D)
                                         .arg(dPK)
                                         .arg(T)
                                         .arg(tPK)
                                         .arg(dPM)
                                         .arg(DBP)
                                         .arg(dDBP)
                                         .arg(BONUS)
                                         .arg(score);

    return score;
}

double radians(double degree)
{
    return degree * 3.14159265 / 180.0;
}

float LogData::calculateDistanceBetweenTwoGPSLocations(APPGPSLocation & first, APPGPSLocation & other)
{
    const double R = 6371000.0; // Earth's radius in meters
    double lat1 = radians(first.getLat());
    double lat2 = radians(other.getLat());
    double diffLat = radians(other.getLat() - first.getLat());
    double diffLon = radians(other.getLon() - first.getLon());

    double a = sin(diffLat / 2) * sin(diffLat / 2) +
               cos(lat1) * cos(lat2) *
                   sin(diffLon / 2) * sin(diffLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = R * c;

    return distance;
}

float LogData::calculateDistanceBetweenWaypoints() {
    float totalDistance = 0.0f;

    if (gameWaypoints.size() < 2) {
        // Not enough waypoints to calculate distance
        return totalDistance;
    }

    for (size_t i = 1; i < gameWaypoints.size(); ++i) {
        totalDistance += calculateDistanceBetweenTwoGPSLocations(gameWaypoints[i-1].getLocation(), gameWaypoints[i].getLocation());
    }

    return totalDistance/1000;
}


float LogData::calculateDistanceWalked() {
    float totalDistance = 0.0f;

    if (recordedLocations.size() < 2) {
        // Not enough points to calculate distance
        return totalDistance;
    }

    for (size_t i = 1; i < recordedLocations.size(); ++i) {
        totalDistance += calculateDistanceBetweenTwoGPSLocations(recordedLocations[i-1], recordedLocations[i]);
    }

    return totalDistance/1000;
}





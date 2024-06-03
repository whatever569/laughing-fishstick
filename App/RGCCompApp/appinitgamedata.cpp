#include "appinitgamedata.h"

APPInitGameData::APPInitGameData(std::vector<APPWaypoint> &wps, std::string uName)
    : waypoints(wps), userName(uName) {}

APPInitGameData::APPInitGameData() : waypoints(), userName("") {}

APPInitGameData::~APPInitGameData() {}

APPInitGameData::APPInitGameData(const APPInitGameData &other)
    : waypoints(other.waypoints), userName(other.userName) {}

APPInitGameData& APPInitGameData::operator=(const APPInitGameData &other) {
    if (this != &other) {  // Check for self-assignment
        waypoints = other.waypoints;
        userName = other.userName;
    }
    return *this;
}

void APPInitGameData::setWaypoints(std::vector<APPWaypoint> &wps) {
    waypoints = wps;
}

void APPInitGameData::setUserName(std::string name) {
    userName = name;
}

std::vector<APPWaypoint>& APPInitGameData::getWaypoints() {
    return waypoints;
}

std::string APPInitGameData::getUserName() const {
    return userName;
}

bool APPInitGameData::isDataComplete()
{
    if(waypoints.size() == 0)
    {
        return false;
    }
    for (APPWaypoint wp : waypoints)
    {
        if(!wp.getIsComplete())
        {
            return false;
        }
    }
    return (userName != "");
}

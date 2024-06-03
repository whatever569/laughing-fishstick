#ifndef APPINITGAMEDATA_H
#define APPINITGAMEDATA_H
#include <vector>
#include <string>
#include <appwaypoint.h>

class APPInitGameData {
public:
    APPInitGameData(std::vector<APPWaypoint> &wps, std::string uName);
    APPInitGameData();
    ~APPInitGameData();  // Destructor
    APPInitGameData(const APPInitGameData &other);  // Copy constructor
    APPInitGameData& operator=(const APPInitGameData &other);  // Copy assignment operator

    void setWaypoints(std::vector<APPWaypoint> &wps);
    void setUserName(std::string name);
    std::vector<APPWaypoint>& getWaypoints();
    std::string getUserName() const;
    bool isDataComplete();
private:
    std::vector<APPWaypoint> waypoints;
    std::string userName;
};


#endif // APPINITGAMEDATA_H

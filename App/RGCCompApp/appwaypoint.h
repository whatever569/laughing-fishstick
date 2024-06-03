#ifndef APPWAYPOINT_H
#define APPWAYPOINT_H
#include <appgpslocation.h>
#include <string>
#include <iostream>
enum Puzzles
{
    SimonSays,
    COUNT,//to iterate over enum cases and is also used as the init value
};
std::string getPuzzleName(Puzzles p);

class APPWaypoint
{
public:
    APPWaypoint();
    ~APPWaypoint();
    APPWaypoint(APPGPSLocation &loc, Puzzles puz);
    void setPuzzle(Puzzles puz);
    void setLocation(APPGPSLocation &loc);
    Puzzles getPuzzle(void);
    APPGPSLocation &getLocation(void);
    bool getIsComplete(void);
    APPWaypoint(const APPWaypoint& other);  // Copy constructor
    APPWaypoint& operator=(const APPWaypoint& other);  // Assignment operator
    bool operator==(const APPWaypoint& other) const;

private:
    Puzzles puzzle;
    APPGPSLocation location;
    const float EPSILON = 0.1f;
};

#endif // APPWAYPOINT_H

#include "appwaypoint.h"

APPWaypoint::APPWaypoint(APPGPSLocation &loc, Puzzles puz)
    : puzzle(puz), location(loc)
{
}
APPWaypoint::APPWaypoint(){
    puzzle = COUNT;
    location = APPGPSLocation();
}
APPWaypoint::~APPWaypoint(){
}
APPGPSLocation &APPWaypoint::getLocation()
{
    return location;
}
Puzzles APPWaypoint::getPuzzle()
{
    return puzzle;
}

void APPWaypoint::setLocation(APPGPSLocation &loc)
{
    location = loc;
}

void APPWaypoint::setPuzzle(Puzzles puz)
{
    puzzle = puz;
    APPGPSLocation defaultLocation = APPGPSLocation();
}

std::string getPuzzleName(Puzzles p)
{
    switch(p){
    case (SimonSays):
        return "Simon Says";
        break;
    case (COUNT):
        return "Puzzle not selected";
        break;
    }
}

bool APPWaypoint::getIsComplete()
{
    bool isDataComplete;
    if(puzzle == COUNT) //COUNT is the default
    {
        isDataComplete = false;
    } else if(fabs(location.getLat() - APPGPSLocation::defaultLatitude) < EPSILON || fabs(location.getLon() - APPGPSLocation::defaultLongitude) < EPSILON)
    {
        isDataComplete = false;
    }
    else
    {
        isDataComplete = true;
    }
    return isDataComplete;
}

// Copy constructor
APPWaypoint::APPWaypoint(const APPWaypoint& other)
    : puzzle(other.puzzle), location(other.location) {}

// Assignment operator
APPWaypoint& APPWaypoint::operator=(const APPWaypoint& other) {
    if (this != &other) {  // Check for self-assignment
        puzzle = other.puzzle;
        location = other.location;
    }
    return *this;
}

bool APPWaypoint::operator==(const APPWaypoint& other)  const{
    return puzzle == other.puzzle &&
           location == other.location;
}


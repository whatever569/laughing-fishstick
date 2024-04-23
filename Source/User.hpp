#ifndef USER_H
#define USER_H
#include <string>
#include <GPSLocation.hpp>
using namespace std;
class User
{
    public:
        User* userSingelton;
        string username = "Unassigned at intialization";
    GPSLocation getUsersCurrentLocation()
    {
        GPSLocation currentLocation {GPSLocation()};
        //Todo
        return currentLocation;
    }
};
#endif
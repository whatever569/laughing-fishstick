#ifndef USER_H
#define USER_H
#include <string>
#include <GPSLocation.hpp>
using namespace std;
class User
{
    public:
        static User* userSingelton;
        string username = "Unassigned at intialization";
        int timeDirectionButtonPressed;
    GPSLocation getUsersCurrentLocation()
    {
        GPSLocation currentLocation {GPSLocation()};
        //Todo
        return currentLocation;
    }
};
#endif
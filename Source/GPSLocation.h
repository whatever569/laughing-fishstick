#ifndef GPSLOCATION_H
#define GPSLOCATION_H
#include <cmath>

#define PI 3.14159265

///@brief GPSLocation is the class representing a gps coordinate, with a few helper functions
class GPSLocation
{
private:
    double latitude;  // in degrees
    double longitude; // in degrees
    bool isConnected = false;

public:
    GPSLocation(double lat = 0.0, double lon = 0.0) : latitude(lat), longitude(lon) {}

    // remember to protect this code from interrrupts
    void setLatitude(double lat)
    {
        latitude = lat;
    }

    void setLongitude(double lon)
    {
        longitude = lon;
    }

    double getLatitude() const
    {
        return latitude;
    }

    double getLongitude() const
    {
        return longitude;
    }

    void setIsConnected(bool b)
    {
        isConnected = b;
    }

    bool getIsConnected()
    {
        return isConnected;
    }

    /// @brief Calculate distance between this location and another location using the Haversine formula
    double distanceTo(const GPSLocation &other) const
    {
        const double R = 6371000.0; // Earth's radius in meters
        double lat1 = radians(latitude);
        double lat2 = radians(other.latitude);
        double diffLat = radians(other.latitude - latitude);
        double diffLon = radians(other.longitude - longitude);

        double a = sin(diffLat / 2) * sin(diffLat / 2) +
                   cos(lat1) * cos(lat2) *
                       sin(diffLon / 2) * sin(diffLon / 2);
        double c = 2 * atan2(sqrt(a), sqrt(1 - a));
        double distance = R * c;

        return distance;
    }

    /// @brief returns true if the GPSLocation is within a certain threshold around another GPSLocation
    /// @param other the other GPSLocation
    /// @param accuracyInMeters default is 5meters
    /// @return
    bool isEqualToWithInRange(const GPSLocation &other, double accuracyInMeters = 5.0)
    {
        return (distanceTo(other) <= accuracyInMeters);
    }

private:
    // Convert degree to radians
    static double radians(double degree)
    {
        return degree * PI / 180.0;
    }
};
#endif
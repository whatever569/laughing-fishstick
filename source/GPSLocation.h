#ifndef GPSLOCATION_H
#define GPSLOCATION_H
#include <cmath>
#include "GPS/GPS.h"

#define PI 3.14159265
#define EARTH_RADIUS 6371000.0f 

///@brief GPSLocation is the class representing a gps coordinate, with a few helper functions
class GPSLocation
{
private:
    double latitude;  // in degrees
    double longitude; // in degrees
    bool isConnected = false;

public:
    enum Direction
    {
        UP,
		DOWN,
		LEFT,
		RIGHT,
    };
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
	
	void setCoordinates(double lat, double lon) {
		latitude = lat;
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
        double lat1 = radians(latitude);
        double lat2 = radians(other.latitude);
        double diffLat = radians(other.latitude - latitude);
        double diffLon = radians(other.longitude - longitude);

        double a = sin(diffLat / 2) * sin(diffLat / 2) +
                   cos(lat1) * cos(lat2) *
                       sin(diffLon / 2) * sin(diffLon / 2);
        double c = 2 * atan2(sqrt(a), sqrt(1 - a));
        double distance = EARTH_RADIUS * c;

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

    Direction getDirection(const GPSLocation &other)
    {
        float lat_diff = other.latitude - latitude;
        float lon_diff = other.longitude - longitude;

        if (fabs(lat_diff) > fabs(lon_diff))
        {
            if (lat_diff > 0)
            {
                return UP;
            }
            else
            {
                return DOWN;
            }
        }
        else
        {
            if (lon_diff > 0)
            {
                return RIGHT;
            }
            else
            {
                return LEFT;
            }
        }
    }

private:
    // Convert degree to radians
    static double radians(double degree)
    {
        return degree * PI / 180.0;
    }
};

#endif
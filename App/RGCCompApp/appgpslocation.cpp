#include "appgpslocation.h"
// const float APPGPSLocation::defaultLatitude;
// const float APPGPSLocation::defaultLongitude;
APPGPSLocation::APPGPSLocation(float lat, float lon)
    : latitude(lat), longitude(lon)
{}

float APPGPSLocation::getLat()
{
    return latitude;
}

float APPGPSLocation::getLon()
{
    return longitude;
}

APPGPSLocation::APPGPSLocation(const APPGPSLocation& other)
    : latitude(other.latitude), longitude(other.longitude) {}

// Assignment operator
APPGPSLocation& APPGPSLocation::operator=(const APPGPSLocation& other) {
    if (this != &other) {  // Check for self-assignment
        latitude = other.latitude;
        longitude = other.longitude;
    }
    return *this;
}

// Equality operator
bool APPGPSLocation::operator==(const APPGPSLocation& other) const {
    return (latitude == other.latitude) && (longitude == other.longitude);
}


void APPGPSLocation::setLat(float lat)
{
    latitude = lat;
}

void APPGPSLocation::setLon(float lon)
{
    longitude = lon;
}
APPGPSLocation::APPGPSLocation()
{
    longitude = defaultLongitude;
    latitude = defaultLatitude;
}

APPGPSLocation::~APPGPSLocation()
{}


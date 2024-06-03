#ifndef APPGPSLOCATION_H
#define APPGPSLOCATION_H

class APPGPSLocation
{
public:
    APPGPSLocation(float lat, float lon);
    void setLat(float lat);
    float getLat(void);
    void setLon(float lon);
    float getLon(void);
    APPGPSLocation();
    APPGPSLocation(const APPGPSLocation& other);  // Copy constructor
    APPGPSLocation& operator=(const APPGPSLocation& other);  // Assignment operator
    bool operator==(const APPGPSLocation& other) const;  // Equality operator
    ~APPGPSLocation();
    constexpr static const float defaultLatitude = 99999, defaultLongitude = 9999;
private:
    float latitude;
    float longitude;
};

#endif // APPGPSLOCATION_H

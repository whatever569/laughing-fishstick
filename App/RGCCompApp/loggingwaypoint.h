#ifndef LOGGINGWAYPOINT_H
#define LOGGINGWAYPOINT_H
#include <appwaypoint.h>
class LoggingWaypoint : public APPWaypoint
{
public:
    LoggingWaypoint();
    ~LoggingWaypoint();

    // Copy constructor
    LoggingWaypoint(const LoggingWaypoint& other);

    // Copy assignment operator
    LoggingWaypoint& operator=(const LoggingWaypoint& other);

    // Equality check operator
    bool operator==(const LoggingWaypoint& other) const;

    // Getters
    bool getIsPuzzleComplete() const;
    bool getIsReached() const;
    float getTimeReachedAfterTheStartOfTheGame() const;

    // Setters
    void setIsPuzzleComplete(bool isComplete);
    void setIsReached(bool reached);
    void setTimeReachedAfterTheStartOfTheGame(float time);

private:
    bool isPuzzleComplete;
    bool isReached;
    float timeReachedAfterTheStartOfTheGame;
};

#endif // LOGGINGWAYPOINT_H

#include "loggingwaypoint.h"

LoggingWaypoint::LoggingWaypoint()
    : isPuzzleComplete(false), isReached(false), timeReachedAfterTheStartOfTheGame(0.0f) {}

// Destructor
LoggingWaypoint::~LoggingWaypoint() {}

// Copy constructor
LoggingWaypoint::LoggingWaypoint(const LoggingWaypoint& other)
    : APPWaypoint(other),
    isPuzzleComplete(other.isPuzzleComplete),
    isReached(other.isReached),
    timeReachedAfterTheStartOfTheGame(other.timeReachedAfterTheStartOfTheGame) {}

// Copy assignment operator
LoggingWaypoint& LoggingWaypoint::operator=(const LoggingWaypoint& other) {
    if (this != &other) {
        APPWaypoint::operator=(other); // Call base class assignment operator
        isPuzzleComplete = other.isPuzzleComplete;
        isReached = other.isReached;
        timeReachedAfterTheStartOfTheGame = other.timeReachedAfterTheStartOfTheGame;
    }
    return *this;
}

// Equality check operator
bool LoggingWaypoint::operator==(const LoggingWaypoint& other) const {
    return APPWaypoint::operator==(other) && // Call base class equality operator
           isPuzzleComplete == other.isPuzzleComplete &&
           isReached == other.isReached &&
           fabs(timeReachedAfterTheStartOfTheGame - other.timeReachedAfterTheStartOfTheGame) < 0.1f;
}

// Getters
bool LoggingWaypoint::getIsPuzzleComplete() const {
    return isPuzzleComplete;
}

bool LoggingWaypoint::getIsReached() const {
    return isReached;
}

float LoggingWaypoint::getTimeReachedAfterTheStartOfTheGame() const {
    return timeReachedAfterTheStartOfTheGame;
}

// Setters
void LoggingWaypoint::setIsPuzzleComplete(bool isComplete) {
    isPuzzleComplete = isComplete;
}

void LoggingWaypoint::setIsReached(bool reached) {
    isReached = reached;
}

void LoggingWaypoint::setTimeReachedAfterTheStartOfTheGame(float time) {
    timeReachedAfterTheStartOfTheGame = time;
}

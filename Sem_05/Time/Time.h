#pragma once

#include <iostream>

constexpr unsigned SECONDS_IN_HOUR = 3600;
constexpr unsigned SECONDS_IN_MINUTE = 60;
constexpr unsigned DAY_SECONDS = 24 * 3600;

class Time
{
private:
    unsigned secondsFromMidnight = 0;

    bool validateAndSet(unsigned lowerBound, unsigned upperBound, unsigned newValue, unsigned oldValue, unsigned multiplier);

public:
    Time() = default;
    Time(unsigned hours, unsigned minutes, unsigned seconds);

    bool setHours(unsigned hours);
    bool setMinutes(unsigned minutes);
    bool setSeconds(unsigned seconds);

    unsigned getHours() const;
    unsigned getMinutes() const;
    unsigned getSeconds() const;
    unsigned getTimeInSeconds() const;

    void tick();
    void serialize(std::ostream& os) const;
    
    Time getRemainingTimeToMidnight() const;
    bool isDinnerTime() const;
    bool isPartyTime() const;
};

int compareTimes(const Time& lhs, const Time& rhs);

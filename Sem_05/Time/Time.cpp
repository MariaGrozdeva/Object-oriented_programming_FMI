#include "Time.h"

#include <iostream>
#include <iomanip>

Time::Time(unsigned hours, unsigned mins, unsigned seconds)
{
    setHours(hours);
    setMinutes(mins);
    setSeconds(seconds);
}

bool Time::setHours(unsigned hours)
{
    return validateAndSet(0, 23, hours, getHours(), SECONDS_IN_HOUR);
}

bool Time::setMinutes(unsigned minutes)
{
    return validateAndSet(0, 59, minutes, getMinutes(), SECONDS_IN_MINUTE);
}

bool Time::setSeconds(unsigned seconds)
{
    return validateAndSet(0, 59, seconds, getSeconds(), 1);
}

unsigned Time::getHours() const
{
    return secondsFromMidnight / SECONDS_IN_HOUR;
}

unsigned Time::getMinutes() const
{
    return (secondsFromMidnight / SECONDS_IN_MINUTE) % 60;
}

unsigned Time::getSeconds() const
{
    return secondsFromMidnight % 60;
}

unsigned Time::getTimeInSeconds() const
{
    return secondsFromMidnight;
}

void Time::tick()
{
    ++secondsFromMidnight %= DAY_SECONDS;
}

void Time::serialize(std::ostream& os) const
{
    using namespace std;
    os << setw(2) << setfill('0') << getHours() << ":"
        << setw(2) << setfill('0') << getMinutes() << ":"
        << setw(2) << setfill('0') << getSeconds() << endl;
}

bool Time::validateAndSet(unsigned lowerBound, unsigned upperBound, unsigned newValue, unsigned oldValue, unsigned multiplier)
{
    if (newValue >= lowerBound && newValue <= upperBound)
    {
        (secondsFromMidnight -= (oldValue * multiplier)) += (newValue * multiplier);
        return true;
    }
    return false;
}

int compareTimes(const Time& lhs, const Time& rhs)
{
    if (lhs.getTimeInSeconds() < rhs.getTimeInSeconds())
    {
        return -1;
    }
    if (lhs.getTimeInSeconds() > rhs.getTimeInSeconds())
    {
        return 1;
    }
    return 0;
}

Time Time::getRemainingTimeToMidnight() const
{
        unsigned remainingSeconds = DAY_SECONDS - secondsFromMidnight;

        if (remainingSeconds == DAY_SECONDS)
        {
                remainingSeconds = 0;
        }

        unsigned hours = remainingSeconds / SECONDS_IN_HOUR;
        unsigned minutes = (remainingSeconds / SECONDS_IN_MINUTE) % 60;
        unsigned seconds = remainingSeconds % 60;

        return Time(hours, minutes, seconds);
}

bool Time::isDinnerTime() const
{
        Time dinnerStart(20, 30, 0);
        Time dinnerEnd(22, 0, 0);

        return compareTimes(*this, dinnerStart) >= 0 && compareTimes(*this, dinnerEnd) <= 0;
}

bool Time::isPartyTime() const
{
        Time partyStart(23, 0, 0);
        Time partyEnd(6, 0, 0);

        return compareTimes(*this, partyStart) >= 0 || compareTimes(*this, partyEnd) <= 0;
}

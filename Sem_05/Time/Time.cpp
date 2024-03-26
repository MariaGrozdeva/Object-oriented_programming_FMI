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
    return validateAndSet(0, 23, hours, getHours(), SECONDS_IN_HOURS);
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
    return secondsFromMidnight / SECONDS_IN_HOURS;
}

unsigned Time::getMinutes() const
{
    return (secondsFromMidnight / SECONDS_IN_MINUTE) % 60;
}

unsigned Time::getSeconds() const
{
    return secondsFromMidnight % 60;
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
    else
    {
        return false;
    }
}

int compareTimes(const Time& lhs, const Time& rhs)
{
    // We don't have access to secondsFromMidnight field.
    // We don't know what 'static' and 'friend' keywords are at this point of the course.

    if (lhs.getHours() == lhs.getHours())
    {
        if (lhs.getMinutes() == rhs.getMinutes())
        {
            return lhs.getSeconds() - rhs.getSeconds();
        }
        else
        {
            return lhs.getMinutes() - rhs.getMinutes();
        }
    }
    else
    {
        return lhs.getHours() - rhs.getHours();
    }
}
#include "GPSPath.h"

GPSPath::GPSPath()
{
    path = new GPSPath::Point[capacity];
}

GPSPath::GPSPath(const GPSPath& other)
{
    path = new GPSPath::Point[other.capacity];
    for (size_t i = 0; i < other.count; i++)
    {
        path[i] = other.path[i];
    }

    capacity = other.capacity;
    count = other.count;
    pathLength = other.pathLength;
}

GPSPath& GPSPath::operator=(const GPSPath& other)
{
    if (this != &other)
    {
        GPSPath::Point* newPath = new GPSPath::Point[other.capacity];
        for (size_t i = 0; i < other.count; i++)
        {
            newPath[i] = other.path[i];
        }

        delete[] path;
        path = newPath;
        capacity = other.capacity;
        count = other.count;
        pathLength = other.pathLength;
    }
    return *this;
}

GPSPath::~GPSPath()
{
    delete[] path;
}

void GPSPath::addPoint(int x, int y)
{
    if (count == capacity)
    {
        resize(capacity * 2);
    }

    Point newPoint{ x, y };
    path[count++] = newPoint;
    if (count > 1)
    {
        pathLength += path[count - 2].getDist(path[count - 1]);
    }
}

void GPSPath::changePoint(int x, int y, unsigned index)
{
    if (index >= count)
    {
        return;
    }

    const Point& currentPoint = path[index];
    Point newPoint{ x, y };

    if (count == 1)
    {
        path[index] = newPoint;
        return;
    }
    
    if (index == 0 && count > 1)
    {
        const Point& nextPoint = path[index + 1];
        float oldDist = currentPoint.getDist(nextPoint);

        (pathLength -= oldDist) += newPoint.getDist(nextPoint);
    }
    else if (index == count - 1 && count > 1)
    {
        const Point& prevPoint = path[index - 1];
        float oldDist = currentPoint.getDist(prevPoint);

        (pathLength -= oldDist) += newPoint.getDist(prevPoint);
    }
    else
    {
        const Point& prevPoint = path[index - 1];
        float oldDist1 = currentPoint.getDist(prevPoint);

        const Point& nextPoint = path[index + 1];
        float oldDist2 = currentPoint.getDist(nextPoint);

        pathLength -= (oldDist1 + oldDist2);
        pathLength += (newPoint.getDist(prevPoint) + newPoint.getDist(nextPoint));
    }

    path[index] = newPoint;
}

float GPSPath::getDistance() const
{
    return pathLength;
}

void GPSPath::resize(size_t newCapacity)
{
    GPSPath::Point* temp = new GPSPath::Point[capacity];
    for (size_t i = 0; i < count; i++)
    {
        temp[i] = path[i];
    }

    delete[] path;
    path = temp;
    capacity = newCapacity;
}

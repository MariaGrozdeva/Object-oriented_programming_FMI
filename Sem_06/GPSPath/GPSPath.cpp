#include "GPSPath.h"

GPSPath::GPSPath()
{
    path = new GPSPath::Point[capacity];
}
GPSPath::GPSPath(const GPSPath& other)
{
    copyFrom(other);
}
GPSPath& GPSPath::operator=(const GPSPath& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}
GPSPath::~GPSPath()
{
    free();
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
    capacity = newCapacity;

    GPSPath::Point* temp = new GPSPath::Point[capacity];
    for (size_t i = 0; i < count; i++)
    {
        temp[i] = path[i];
    }

    delete[] path;
    path = temp;
}

void GPSPath::copyFrom(const GPSPath& other)
{
    capacity = other.capacity;
    count = other.count;

    path = new GPSPath::Point[capacity];
    for (size_t i = 0; i < count; i++)
    {
        path[i] = other.path[i];
    }

    pathLength = other.pathLength;
}
void GPSPath::free()
{
    delete[] path;
    path = nullptr;
    capacity = count = pathLength = 0;
}
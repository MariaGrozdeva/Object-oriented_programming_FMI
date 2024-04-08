#pragma once
#include <cmath>

class GPSPath
{
private:
    struct Point
    {
        int x;
        int y;
        float getDist(const Point& other) const
        {
            int dx = x - other.x;
            int dy = y - other.y;
            return sqrt(dx * dx + dy * dy);
        }
    };

    Point* path = nullptr;
    size_t capacity = 8;
    size_t count = 0;

    float pathLength = 0;

private:
    void resize(size_t newCapacity);

    void copyFrom(const GPSPath& other);
    void free();

public:
    GPSPath();
    GPSPath(const GPSPath& other);
    GPSPath& operator=(const GPSPath& other);
    ~GPSPath();

    void addPoint(int x, int y);
    void changePoint(int x, int y, unsigned index);

    float getDistance() const;
};

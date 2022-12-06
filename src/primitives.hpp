
#ifndef __PRIMITIVES_HPP__
#define __PRIMITIVES_HPP__

#include <cmath>
/**
 * @brief A point in long lat space. 
 */
class Point
{
public:
    Point(double longitude, double latitude):longitude(longitude),latitude(latitude) {}
    double Longitute()
    {
        return longitude;
    }
    double Latitude()
    {
        return latitude;
    }
private:
    double longitude;
    double latitude;
};

static const Point bad_point = Point(nan("") ,nan(""));
/**
 * @brief A class containing a rectangle in long lat space.
 * 
 * A region never spans the date line and cannot have a pole within it.
 * One edge can run along the date line. Also the top ot bottom edge could represent a pole.
 * 
 */
class Region
{
public:
    Region(double west, double east, double south, double north):west(west),east(east),south(south),north(north) {}
    bool Contains(Point point);
private:
    double west;
    double east;
    double south;
    double north;
};

#endif

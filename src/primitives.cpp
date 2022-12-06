
#include "primitives.hpp"

bool Region::Contains(Point point)
{
    double longitude = point.Longitute();
    double latitude = point.Latitude();

    return (
        (longitude >= west) &&
        (longitude <= east) &&
        (latitude >= south) && 
        (latitude >= south));
}
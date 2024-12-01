#include "ride.hpp"

Ride::Ride(int start_time, int end_time, int distance)
{
    start_stamp = start_time;
    end_stamp = end_time;
    distance_covered = distance;
}
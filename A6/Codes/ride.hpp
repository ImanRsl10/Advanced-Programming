#pragma once

class Ride {
public:
    Ride(int start_time, int end_time, int distance);
    int get_distance() { return distance_covered; }
    int begin() { return start_stamp; }
    int end() { return end_stamp; }
private:
    int start_stamp;
    int end_stamp;
    int distance_covered;
};
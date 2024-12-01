#pragma once

#include "constants.hpp"

class Mission {
public:
    Mission(int id, int start_time, int end_time);
    bool is_id_match(int id) { return this->id == id; }
    bool is_ride_in_interval(int start_time, int end_time);
    void show_info(int end_time);
    int get_start_time_stamp() const { return start_time_stamp; }
    virtual int progress_amount(int start_time, int end_time, int distance) = 0;
    virtual bool is_passed(int data) = 0;
protected:
    int id;
    int start_time_stamp;
    int end_time_stamp;
    int reward;
};

class Time_mission : public Mission {
public:
    Time_mission(int id, int start_time, int end_time, int target_time, int reward);
    int progress_amount(int start_time, int end_time, int distance) { return end_time - start_time; }
    bool is_passed(int elapsed_time) { return target_time <= elapsed_time; }
private:
    int target_time;
};

class Distance_mission : public Mission {
public:
    Distance_mission(int id, int start_time, int end_time, int target_distance, int reward);
    int progress_amount(int start_time, int end_time, int distance) { return distance; }
    bool is_passed(int distance_covered) { return target_distance <= distance_covered; }
private:
    int target_distance;
};

class Count_mission : public Mission {
public:
    Count_mission(int id, int start_time, int end_time, int target_number, int reward);
    int progress_amount(int start_time, int end_time, int distance) { return UNIT; }
    bool is_passed(int count) { return target_number <= count; }
private:
    int target_number;
};

struct Driver_mission
{
    Mission* mission;
    bool status;
    int progress;
    int end_time_stamp;

    Driver_mission(Mission* mission, bool status, int progress, int end_time_stamp)
    : mission(mission), status(status), progress(progress), end_time_stamp(end_time_stamp) {}
};
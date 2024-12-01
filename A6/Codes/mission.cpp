#include "mission.hpp"
#include "functions.hpp"

using namespace std;

Mission::Mission(int id, int start_time, int end_time)
{
    this->id = id;
    start_time_stamp = start_time;
    end_time_stamp = end_time;
}

bool Mission::is_ride_in_interval(int start_time, int end_time)
{
    return (start_time_stamp <= start_time) && (end_time_stamp >= end_time);
}

void Mission::show_info(int end_time)
{
    cout << "mission " << id << ":" << endl;
    cout << "start timestamp: " << start_time_stamp << endl;
    cout << "end timestamp: " << end_time << endl;
    cout << "reward: " << reward << endl;
}

Time_mission::Time_mission(int id, int start_time, int end_time, int target_time, int reward)
    : Mission(id, start_time, end_time)
{
    this->target_time = to_second(target_time);
    this->reward = reward;
}

Distance_mission::Distance_mission(int id, int start_time, int end_time, int target_distance, int reward)
    : Mission(id, start_time, end_time)
{
    this->target_distance = target_distance;
    this->reward = reward;
}

Count_mission::Count_mission(int id, int start_time, int end_time, int target_number, int reward)
    : Mission(id, start_time, end_time)
{
    this->target_number = target_number;
    this->reward = reward;
}
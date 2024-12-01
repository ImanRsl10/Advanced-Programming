#include "functions.hpp"
#include "constants.hpp"
#include "mission.hpp"

using namespace std;

void print_message(std::string message)
{
    std::cout << message << std::endl;
}

bool is_adding_cmd(string cmd)
{
    return (cmd == ADD_TIME_MISSION) ||
           (cmd == ADD_DISTANCE_MISSION) ||
           (cmd == ADD_COUNT_MISSION);
}

bool validate_interval(int start, int end)
{
    return start < end;
}

int to_second(int minute)
{
    return minute * 60;
}

bool mission_comparator(const Driver_mission* mission1, const Driver_mission* mission2) 
{
    return mission1->mission->get_start_time_stamp() < mission2->mission->get_start_time_stamp();
}
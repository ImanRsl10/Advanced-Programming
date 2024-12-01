#include "driver.hpp"
#include "constants.hpp"
#include "functions.hpp"
#include <algorithm>

using namespace std;

void Driver::assign_mission(Mission* mission, bool status)
{
    Driver_mission* driver_mission = new Driver_mission{mission, status, NO_PROGRESS, INIT_TIME};
    missions.push_back(driver_mission);
}

bool Driver::has_this_mission(int mission_id)
{
    for(Driver_mission* driver_mission : missions)
        if(driver_mission->mission->is_id_match(mission_id))
            return true;
    return false;
}

void Driver::show_completed_missions()
{
    sort(missions.begin(), missions.end(), mission_comparator);
    for(Driver_mission* driver_mission : missions)
    {
        if(driver_mission->status == false)
        {
            if(driver_mission->mission->is_ride_in_interval(current_ride->begin(), current_ride->end()))
            {
                driver_mission->progress += driver_mission->mission->progress_amount(current_ride->begin(),
                                                                                    current_ride->end(),
                                                                                    current_ride->get_distance());
            }
            if(driver_mission->mission->is_passed(driver_mission->progress))
            {
                driver_mission->status = true;
                driver_mission->end_time_stamp = current_ride->end();
                driver_mission->mission->show_info(driver_mission->end_time_stamp);
                cout << endl;
            }       
        }
    }
}

void Driver::show_missions_status()
{
    if(missions.size() != 0)
    {
        for(Driver_mission* driver_mission : missions)
        {
            driver_mission->mission->show_info(driver_mission->end_time_stamp);
            cout << "status: " << status[driver_mission->status] << endl;
            cout << endl;
        }
    }
    else   
        print_message("DRIVER_MISSION_NOT_FOUND");
}
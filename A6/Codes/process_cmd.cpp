#include "process_cmd.hpp"
#include "constants.hpp"
#include "functions.hpp"
#include "mission.hpp"
#include "mission_system.hpp"
#include <iostream>
#include <ios>
#include <limits>

using namespace std;

void add_new_mission(Mission_System& system, string mission_type)
{
    Mission* new_mission;
    int id, start_timestamp, end_timestamp, target, reward_amount;

    cin >> id >> start_timestamp >> end_timestamp >> target >> reward_amount;

    if(!system.find_mission_by_id(id))
    {
        if(validate_interval(start_timestamp, end_timestamp) && target > 0 && reward_amount > 0)
        {
            if(mission_type == ADD_TIME_MISSION)
                new_mission = new Time_mission(id, start_timestamp, end_timestamp, target, reward_amount);
            else if(mission_type == ADD_DISTANCE_MISSION)
                new_mission = new Distance_mission(id, start_timestamp, end_timestamp, target, reward_amount);
            else if(mission_type == ADD_COUNT_MISSION)
                new_mission = new Count_mission(id, start_timestamp, end_timestamp, target, reward_amount);
                
            system.add_mission(new_mission);
            print_message("OK");
        }
        else
            print_message("INVALID_ARGUMENTS");
    }
    else
        print_message("DUPLICATE_MISSION_ID");
}

void assign_mission(Mission_System& system)
{
    int mission_id, driver_id;
    cin >> mission_id >> driver_id;

    Mission* mission = system.find_mission_by_id(mission_id);
    Driver* agent_driver = system.find_driver_by_id(driver_id);

    if(mission != NULL)
    {
        if(agent_driver != NULL)
        {
            if(!agent_driver->has_this_mission(mission_id)) 
            {
                agent_driver->assign_mission(mission);
                print_message("OK");
            }
            else
                print_message("DUPLICATE_DRIVER_MISSION");
        }
        else //make a driver in system with that id
        {
            Driver* new_driver = new Driver(driver_id);
            new_driver->assign_mission(mission);
            system.add_driver(new_driver);
            print_message("OK"); 
        }
    }
    else
        print_message("MISSION_NOT_FOUND");
}

void set_ride(Mission_System& system)
{
    int start_stamp, end_stamp, driver_id, distance;
    cin >> start_stamp >> end_stamp >> driver_id >> distance;
    
    Driver* driver = system.find_driver_by_id(driver_id);
    if(validate_interval(start_stamp, end_stamp))
    {
        if(driver != NULL)
        {
            driver->add_ride(start_stamp, end_stamp, distance);
            cout << "completed missions for driver " << driver_id << ":" << endl;
            driver->show_completed_missions();
        }
    }
    else
        print_message("INVALID_ARGUMENTS");
}

void show_missions_status(Mission_System& system)
{
    int driver_id;
    cin >> driver_id;
    Driver* driver = system.find_driver_by_id(driver_id);
    
    if(driver != NULL)
    {
        cout << "missions status for driver " << driver_id << ":" << endl;
        driver->show_missions_status();
    }
    else
        print_message("MISSION_NOT_FOUND");
}

void process_command(Mission_System& system)
{
    string command;
    while (cin >> command)
    {
        if(is_adding_cmd(command))
        {
            add_new_mission(system, command);
        }

        else if(command == ASSIGN_MISSION)
        {
            assign_mission(system);
        }
        else if(command == RECORD_RIDE)
        {
            set_ride(system);
        }
        else if(command == SHOW_MISSIONS_STATUS)
        {
            show_missions_status(system);
        }
        else
        {
            print_message("INVALID_ARGUMENTS");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}
#include "mission_system.hpp"
#include <iostream>

Mission_System::~Mission_System()
{
    for(int i = 0; i < missions.size(); i++)
        delete missions[i];
    for(int i = 0; i < drivers.size(); i++)
        delete drivers[i];
}

Mission* Mission_System::find_mission_by_id(int id)
{
    for(Mission* mission : missions)
        if(mission->is_id_match(id))
            return mission;
    return NULL;
}

Driver* Mission_System::find_driver_by_id(int driver_id)
{
    for(Driver* driver : drivers)
        if(driver->is_id_match(driver_id))
            return driver;
    return NULL;
}
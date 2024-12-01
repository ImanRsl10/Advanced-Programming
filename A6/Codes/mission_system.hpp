#pragma once

#include <vector>
#include "mission.hpp"
#include "driver.hpp"

class Mission_System {
public:
    Mission_System() {}
    ~Mission_System();
    Mission* find_mission_by_id(int id);
    Driver* find_driver_by_id(int driver_id);
    void add_mission(Mission* mission) { missions.push_back(mission); }
    void add_driver(Driver* driver) { drivers.push_back(driver); }
private:
    std::vector <Mission*> missions;
    std::vector <Driver*> drivers;
};
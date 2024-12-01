#pragma once

#include <vector>
#include <map>
#include "mission.hpp"
#include "ride.hpp"

class Driver {
public:
    Driver(int id) : id(id) { status[false] = "ongoing"; status[true] = "completed"; }
    void assign_mission(Mission* mission, bool status = false);
    bool is_id_match(int id) { return this->id == id; }
    bool has_this_mission(int mission_id);
    void add_ride(int start, int end, int distance) { current_ride = new Ride(start, end, distance); }
    void show_completed_missions();
    void show_missions_status();
private:
    int id;
    std::vector <Driver_mission*> missions;
    std::map<bool, std::string> status;
    Ride* current_ride;
};
#pragma once
#include <string>
#include "mission_system.hpp"

void add_new_mission(Mission_System& system, std::string mission_type);
void assign_mission(Mission_System& system);
void set_ride(Mission_System& system);
void show_missions_status(Mission_System& system);
void process_command(Mission_System& system);
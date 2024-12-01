#pragma once

#include <iostream>
#include "mission.hpp"

void print_message(std::string message);
bool is_adding_cmd(std::string cmd);
bool validate_interval(int start, int end);
int to_second(int minute);
bool mission_comparator(const Driver_mission* mission1, const Driver_mission* mission2);
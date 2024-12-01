#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "structs.hpp"
#include "week.hpp"
#include "team.hpp"
#include "league.hpp"

std::vector <std::string> read_csv(std::string filename);

std::pair <std::string, int> extract_player_info(std::string player_info);

void add_player(League* league, Team* team, std::vector <std::string> players, std::string role);

void assign_data(League* league, std::vector <std::string> seperated_line);

void assign_data(Week* week, std::vector <std::string> seperated_line);

Match handle_match_info(std::vector <std::string> match_teams_names, std::vector <std::string> match_teams_goals,
                        std::vector <std::string> host_squad, std::vector <std::string> visiting_team,
                        std::vector <Goal_info> goals);

std::vector <Goal_info> handle_goals_info(std::vector <std::string> goals_assists_info);
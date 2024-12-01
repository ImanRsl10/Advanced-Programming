#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "structs.hpp"
#include "week.hpp"
#include "team.hpp"
#include "league.hpp"

std::vector <std::string> read_csv(std::string filename);

void add_player(League* league, Team* team, std::vector <std::string> players, std::string role);

void assign_data(League* league, std::vector <std::string> seperated_line);

void assign_data(Week* week, std::vector <std::string> seperated_line);

Match handle_match_info(std::vector <std::string> match_teams_names, std::vector <std::string> match_teams_goals);

std::vector <Player_score> handle_player_scores_info(std::vector <std::string> players_scores_mixed);

// void set_teams_players_data(std::string filename, League& league);

// void set_weeks_stats(std::string filename_pattern, League& league);
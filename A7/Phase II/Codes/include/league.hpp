#pragma once

#include <string>
#include <vector>

#include "player.hpp"
#include "team.hpp"
#include "week.hpp"

class League {
public:
    League() {};
    // ~League(); Needs Destructor
    void add_player(Player* player) { players.push_back(player); }
    void add_team(Team* team) { teams.push_back(team); }
    void add_week(Week* week) { weeks.push_back(week); }
    void bind_week(Week* curr_week);
    void update_status(int week_num);
    void determine_team_of_the_week(int week_num);
    void print_team_info(std::string team_name, int current_week, std::string role, bool rank);
    void print_table();
    void print_matches_in_week(int week_num) { weeks[week_num]->print_matches(); }
    Player* find_player_by_name(std::string player_name);
private:
    bool is_a_valid_role(std::string role);
    Team* find_team_by_name(std::string team_name);
    std::pair <Player*, Player*> find_best_player(int week_num, std::string role);
    void print_team_of_the_week(Player* best_GK, Player* best_DEF1, Player* best_DEF2,
                                Player* best_MID, Player* best_FORW, int current_week);
    void arrange_table();
private:
    std::vector <Player*> players;
    std::vector <Team*> teams;
    std::vector <Week*> weeks;
};
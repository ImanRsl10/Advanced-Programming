#pragma once

#include <string>
#include <vector>
#include <map>

#include "structs.hpp"
#include "match_team.hpp"

class Match {   
public:
    void add_match_team(std::vector <Match_team> teams);
    std::vector <int> get_teams_score();
    std::vector <int> get_teams_goals() { return {host_team.get_gf(), visiting_team.get_gf()}; }
    int check_if_team_played(std::string team_name);
    void print_info();
    bool is_player_played(std::string player_name);
    void set_goals(std::vector <Goal_info> _goals) { goals = _goals; }
    int check_team_status(std::string player_name);
    int get_player_team_ga(std::string player_name);
    std::pair <int, int> get_player_goals_assists(std::string player_name);
    int get_player_own_goals(std::string player_name);
    int calc_conceded_goals_score(std::string player_name);
private:
    int calc_players_scored_goals(std::vector <std::string> mentioned_players);
private:
    std::map <bool, Match_team> Teams;
    Match_team host_team;
    Match_team visiting_team;
    std::vector <Goal_info> goals;
};
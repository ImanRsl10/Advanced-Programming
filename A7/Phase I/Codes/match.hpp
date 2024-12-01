#pragma once

#include <string>
#include <vector>

#include "structs.hpp"

class Match {   
public:
    void add_match_team(std::vector <Match_team> teams);
    std::vector <int> get_teams_score();
    std::vector <int> get_teams_goals() { return {host_team.GF, visiting_team.GF}; }
    int check_if_team_played(std::string team_name);
    void print_info();
private:
    Match_team host_team;
    Match_team visiting_team;
};

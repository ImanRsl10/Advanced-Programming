#pragma once

#include <string>
#include <vector>

#include "constants.hpp"
#include "player.hpp"

class Team {
public:
    Team(std::string name) : name(name), score(INIT), GF(INIT), GA(INIT), GD(INIT) {}
    void add_team_member(Player* player) { team_members.push_back(player); }
    void update_status(int match_score, int match_gf, int match_ga);
    bool is_name_match(std::string team_name) { return name == team_name; }
    std::string get_name() { return name; }
    int get_score() { return score; }
    int get_gf() { return GF; }
    int get_gd() { return GD; }
    void process_members_info(int current_week, std::string role, bool rank);
    void print_info();
private:
    void print_members_info(std::vector <Player*> team_members, int current_week);
private:
    std::string name;
    int score;
    int GF;
    int GA;
    int GD;
    std::vector <Player*> team_members;
};
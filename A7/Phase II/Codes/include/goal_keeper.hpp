#pragma once

#include "player.hpp"

class Goalkeeper : public Player {
public:
    Goalkeeper(std::string name, int price) : Player(name, price), num_of_clean_sheets(INIT) {}
    bool is_role_match(std::string role) { return role == ROLES[GK]; }
    void calc_raw_score(int current_week);
    void print_full_info(int current_week);
private:
    void update_clean_sheet(int conceded_goal) { num_of_clean_sheets += (!conceded_goal) ? CLEAN_SHEET : CONCEDED; }
private:
    int num_of_clean_sheets;
};
#pragma once

#include "player.hpp"

class Midfielder : public Player {
public:
    Midfielder(std::string name, int price) : Player(name, price), num_of_clean_sheets(INIT),
                                              num_of_goals(INIT), num_of_assists(INIT) {}
    bool is_role_match(std::string role) { return role == ROLES[MID]; }
    void calc_raw_score(int current_week);
    void print_full_info(int current_week);
private:
    void update_clean_sheet(int conceded_goal) { num_of_clean_sheets += (!conceded_goal) ? CLEAN_SHEET : CONCEDED; }
private:
    int num_of_clean_sheets;
    int num_of_goals;
    int num_of_assists;
};
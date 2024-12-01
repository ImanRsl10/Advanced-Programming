#pragma once

#include "player.hpp"

class Forward : public Player {
public:
    Forward(std::string name, int price) : Player(name, price), num_of_goals(INIT),
                                           num_of_assists(INIT) {}
    bool is_role_match(std::string role) { return role == ROLES[FORW]; }
    void calc_raw_score(int current_week);
    void print_full_info(int current_week);
private:    
    int num_of_goals;
    int num_of_assists;
};
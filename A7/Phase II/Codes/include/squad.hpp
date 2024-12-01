#pragma once

#include <iostream>
#include <string>

#include "constants.hpp"
#include "player.hpp"
#include "squad_player.hpp"

class Squad {
public:
    void add_player(Player* player);
    void remove_player(std::string player_name);
    void print(); 
    bool is_team_complete();
    float calc_score_of_week(int current_week);
    Squad& operator=(const Squad& squad);
    void set_captain(std::string player_name);
    int calc_total_cost();
private:
    void sort_defenders();
private:
    Squad_player goalkeeper;
    Squad_player defender1;
    Squad_player defender2;
    Squad_player midfielder;
    Squad_player forward;
};
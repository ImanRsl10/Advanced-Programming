#pragma once

#include <string>

#include "constants.hpp"
#include "player.hpp"

class Squad {
public:
    Squad() : goalkeeper(NULL), defender1(NULL), defender2(NULL), midfielder(NULL), forward(NULL) {}
    void add_player(Player* player);
    void remove_player(std::string player_name);
    void print(); 
    bool is_team_complete() { return goalkeeper != NULL && defender1 != NULL && defender2 != NULL && midfielder != NULL && forward != NULL; }
    float calc_score_of_week(int current_week);
    Squad& operator=(const Squad& squad);
private:
    void sort_defenders();
private:
    Player* goalkeeper;
    Player* defender1;
    Player* defender2;
    Player* midfielder;
    Player* forward;
};
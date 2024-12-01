#pragma once

#include "player.hpp"

class Squad_player {
public:
    Squad_player() : player(NULL), captain(false) {}
    void set(Player* _player) { player = _player; }
    void flush() { player = NULL; captain = false; }
    void set_captain() { captain = true; }
    bool is_empty() { return player == NULL; }
    bool is_name_match(std::string name) { return player->is_name_match(name); }
    std::string get_name() { return player->get_name(); }
    float get_score_of_the_week(int current_week);
    void print_info();
    int get_price() { return player->get_price(); }
private:
    Player* player;
    bool captain;
};
#pragma once

#include <string>

#include "squad.hpp"

class User {
public:
    User(std::string username, std::string pass); 
    bool has_same_name(std::string team_name) { return fantasy_team_name == team_name; } 
    bool is_same_user_name(std::string _username) { return fantasy_team_name == _username; }
    bool is_same_password(std::string _password) { return password == _password; }
    void buy_player(Player* player);
    void sell_player(Player* player);
    void print_squad();
    void set_transfer() { num_of_transfers++; }
    void reset_transfer() { num_of_transfers = INIT; }
    bool is_transfers_complete() { return num_of_transfers == NUM_OF_TRANSFERS; }
    bool is_team_complete() { return team_is_complete; }
    void check_if_team_is_complete(int current_week);
    void update_score(int current_week);
    void update_squad() {submiited_squad = squad;}
    float get_score() { return score; }
    std::string get_fantasy_team_name() { return fantasy_team_name; }
    void print_info();
    void set_captain(std::string player_name) { squad.set_captain(player_name); }
    void show_budget() { }
private:
    std::string fantasy_team_name;
    std::string password;
    Squad squad, submiited_squad;
    float score;
    bool team_is_complete;
    int num_of_transfers;
    int budget;
};
#pragma once

#include <string>
#include <vector>

#include "constants.hpp"
#include "structs.hpp"

class Player {
public:
    Player(std::string name, std::string role) : name(name), role(role), yellow_cards(INIT), weeks_stats(NUM_OF_WEEKS) {}
    bool is_name_match(std::string player_name) { return name == player_name; }
    bool has_role(std::string _role) { return role == _role; }
    void update_status(int this_week, bool injured, bool got_yellow_card,
                       bool got_red_card, float score);
    float get_score_of_the_week(int week_num) { return weeks_stats[week_num].score; } 
    float calc_score_in_interval(int modified_week, int current_week);
    float calc_mean_score(int week_num);
    std::string get_name() { return name; }
    void print_info(int current_week);
    void print_info(int current_week, bool mode);
    bool is_available(int current_week) { return !(weeks_stats[current_week].suspended || weeks_stats[current_week].injured); }
private:
    float calc_total_score(int week_num, int& num_of_matches_played);
    void check_suspension(int next_week, bool got_yellow_card, bool got_red_card);
    void check_injury_status(int next_week);
private:
    std::string name;
    std::string role;
    int yellow_cards;  
    std::vector <Status> weeks_stats;
};
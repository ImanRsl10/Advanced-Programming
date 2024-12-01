#pragma once

#include <string>
#include <vector>

#include "constants.hpp"
#include "structs.hpp"
#include "match.hpp"

class Player {
public:
    Player(std::string name, int price) : name(name), price(price), yellow_cards(INIT), weeks_stats(NUM_OF_WEEKS),
                                          weeks_scores(NUM_OF_WEEKS), raw_scores(NUM_OF_WEEKS) {}
    bool is_name_match(std::string player_name) { return name == player_name; }
    virtual bool is_role_match(std::string _role) = 0;
    void update_status(int this_week, bool injured, bool got_yellow_card, bool got_red_card);
    void add_match(Match* match) { matches.push_back(match); }
    float get_score_of_the_week(int week_num) { return weeks_scores[week_num]; } 
    float get_score_of_the_week(int week_num, bool is_captain);
    float calc_mean_score(int week_num);
    std::string get_name() { return name; }
    void print_info(int current_week);  
    virtual void print_full_info(int current_week) = 0;
    bool is_available(int current_week) { return !(weeks_stats[current_week].suspended || weeks_stats[current_week].injured); }
    void calc_score(int current_week);
    int get_price() { return price; }
private:
    float calc_total_score(int week_num, int& num_of_matches_played);
    void check_suspension(int next_week, bool got_yellow_card, bool got_red_card);
    void check_injury_status(int next_week);
    virtual void calc_raw_score(int current_week) = 0;
protected:
    std::string name;
    std::vector <Status> weeks_stats;
    std::vector <Match*> matches;
    std::vector <float> raw_scores;
private:
    int yellow_cards;  
    std::vector <float> weeks_scores;
    int price;
};
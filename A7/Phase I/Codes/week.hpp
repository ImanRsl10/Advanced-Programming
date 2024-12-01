#pragma once

#include <string>
#include <vector>

#include "player.hpp"
#include "team.hpp"
#include "match.hpp"
#include "structs.hpp"

class Week {
public:
    void set_info(std::vector <std::string> injruies, std::vector <std::string> yellow_cards, 
                  std::vector <std::string> red_cards, std::vector <Player_score> players_scores);
    void add_match(Match match) { mathces.push_back(match); }
    void get_teams(std::vector <Team*> teams) { this->teams = teams; }
    void get_players(std::vector <Player*> players) { this->players = players; }
    void update(int week_num);
    void print_matches();
private:
    bool check_if_mentioned(Player* current_player, std::vector <std::string> mentioned_players);
    float get_player_score(Player* current_player);
    void update_players_status(int week_num);
    void update_teams_status();
    void find_match_team_played(std::string team_name, int& team_score, int& gf, int& ga);
private:
    std::vector <Team*> teams;
    std::vector <Player*> players;
    std::vector <Match> mathces;
    std::vector <std::string> injuries;
    std::vector <std::string> red_cards;
    std::vector <std::string> yellow_cards;
    std::vector <Player_score> players_scores;
};
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
                  std::vector <std::string> red_cards);
    void add_match(Match match) { matches.push_back(match); }
    void set_teams(std::vector <Team*> teams) { this->teams = teams; }
    void set_players(std::vector <Player*> players) { this->players = players; }
    void update(int week_num);
    void print_matches();
private:
    bool check_if_mentioned(Player* current_player, std::vector <std::string> mentioned_players);
    Match* find_match_player_played(std::string player_name);
    void update_players_status(int week_num);
    void update_teams_status();
    void find_match_team_played(std::string team_name, int& team_score, int& gf, int& ga);
private:
    std::vector <Team*> teams;
    std::vector <Player*> players;
    std::vector <Match> matches;
    std::vector <std::string> injuries;
    std::vector <std::string> red_cards;
    std::vector <std::string> yellow_cards;
};
#pragma once

#include <string>
#include <vector>

#include "player.hpp"
#include "team.hpp"
#include "user.hpp"

std::vector <std::string> split_by_identifire(std::string str, char identifire);

void print_message(std::string message);

float calc_Ax(int x);

bool compare_teams_by_name(Team* team1, Team* team2);

std::vector <Player*> find_players_by_role(std::string role, std::vector <Player*> players);

bool compare_players_by_name(Player* player1, Player* player2);

class compare_by_score {
public:
    compare_by_score(int week_num) : curr_week(week_num) {}
    bool operator()(Player* player1, Player* player2);
private:
    int curr_week;
};

bool is_valid_cmd(std::string command, const std::string identifire1, const std::string identifire2,
                  const std::string identifire3, const std::string identifire4);

bool is_valid_cmd(std::string command, const std::string identifire1, const std::string identifire2,
                  const std::string identifire3, const std::string identifire4,
                  const std::string identifire5, const std::string identifire6,
                  const std::string identifire7);

bool is_valid_cmd(std::string command, const std::string identifire1, const std::string identifire2,
                  const std::string identifire3, const std::string identifire4, const std::string identifire5,
                  const std::string identifire6, const std::string identifire7, const std::string identifire8,
                  const std::string identifire9, const std::string identifire10);

std::string assemble_name(std::vector <std::string> splitted_name);

bool compare_users(User* user1, User* user2);
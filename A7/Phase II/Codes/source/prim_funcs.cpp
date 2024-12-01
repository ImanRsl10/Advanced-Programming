#include <iostream>
#include <cmath>

#include "../include/prim_funcs.hpp"

using namespace std;

vector<string> split_by_identifire(string str, char identifire)
{
	vector<string> result;
	int start_pos = INIT;
	while (start_pos < str.length()) 
    {
		int identifire_Pos = str.find(identifire, start_pos);
		if (identifire_Pos == string::npos) 
        {
			result.push_back(str.substr(start_pos));
			break;
		}
		result.push_back(str.substr(start_pos, identifire_Pos - start_pos));
		start_pos = identifire_Pos + 1;
	}
	return result;
}

void print_message(string message)
{
    cout << message << endl;
}

float calc_Ax(int x)
{
    return 10.0 / (1.0 + exp(-x / 6.0));
}

bool compare_teams_by_name(Team* team1, Team* team2)
{
    if(team1->get_score() != team2->get_score())
        return team1->get_score() > team2->get_score();
    
    if(team1->get_gd() != team2->get_gd())
        return team1->get_gd() > team2->get_gd();
    if(team1->get_gf() != team2->get_gf())
        return team1->get_gf() > team2->get_gf();

    return team1->get_name() < team2->get_name();
}

bool compare_players_by_name(Player* player1, Player* player2)
{
    return player1->get_name() < player2->get_name();
}

vector <Player*> find_players_by_role(std::string role, std::vector <Player*> players)
{
    vector <Player*> candidates;
    for(Player* player : players)
        if(player->is_role_match(role))
            candidates.push_back(player);
    return candidates;
}

bool compare_by_score::operator()(Player* player1, Player* player2)
{
    if(player1->calc_mean_score(curr_week) != player2->calc_mean_score(curr_week))
        return player1->calc_mean_score(curr_week) > player2->calc_mean_score(curr_week);

    return compare_players_by_name(player1, player2);
}

bool compare_users(User* user1, User* user2)
{
    if(user1->get_score() != user2->get_score())
        return user1->get_score() > user2->get_score();
    return user1->get_fantasy_team_name() < user2->get_fantasy_team_name();
}
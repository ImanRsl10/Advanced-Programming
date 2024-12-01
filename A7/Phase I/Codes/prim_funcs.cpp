#include <iostream>

#include "constants.hpp"
#include "prim_funcs.hpp"

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

vector <Player*> find_players_by_role(std::string role, std::vector <Player*> players)
{
    vector <Player*> candidates;
    for(Player* player : players)
        if(player->has_role(role))
            candidates.push_back(player);
    return candidates;
}

bool compare_by_name(Player* player1, Player* player2)
{
    return player1->get_name() < player2->get_name();
}

bool compare_by_score::operator()(Player* player1, Player* player2)
{
    if(player1->calc_mean_score(curr_week) != player2->calc_mean_score(curr_week))
        return player1->calc_mean_score(curr_week) > player2->calc_mean_score(curr_week);

    return compare_by_name(player1, player2);
}

bool is_valid_cmd(string command, const string identifire1, const string identifire2,
                  const string identifire3, const string identifire4)
{
    return command == identifire1 || command == identifire2 || command == identifire3 ||
           command == identifire4;
}

bool is_valid_cmd(string command, const string identifire1, const string identifire2,
                  const string identifire3, const string identifire4, const string identifire5,
                  const string identifire6)
{
    return command == identifire1 || command == identifire2 || command == identifire3 ||
           command == identifire4 || command == identifire5 || command == identifire6;
}

bool is_valid_cmd(string command, const string identifire1, const string identifire2,
                  const string identifire3, const string identifire4, const string identifire5,
                  const string identifire6, const string identifire7, const string identifire8,
                  const string identifire9)
{
    return command == identifire1 || command == identifire2 || command == identifire3 ||
           command == identifire4 || command == identifire5 || command == identifire6 ||
           command == identifire7 || command == identifire8 || command == identifire9;
}

string assemble_name(vector <string> splitted_name) //Clean? --> Method or function
{
    string name;
    for(int i = 0; i < splitted_name.size(); i++)
    {
        if(i == splitted_name.size() - 1)
            name += splitted_name[i];
        else
            name += splitted_name[i] + SPACE;
    }
    return name;
}

bool compare_users(User* user1, User* user2)
{
    if(user1->get_score() != user2->get_score())
        return user1->get_score() > user2->get_score();
    return user1->get_fantasy_team_name() < user2->get_fantasy_team_name();
}
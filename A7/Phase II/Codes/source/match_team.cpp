#include "../include/match_team.hpp"
#include "../include/constants.hpp"

using namespace std;

bool Match_team::is_player_in_squad(string player_name)
{
    for(string player : squad)
        if(player == player_name)
            return true;
    return false;
}

int Match_team::find_player_post(string player_name)
{
    int player_post = INIT;
    for(int i = 0; i < squad.size(); i++)
        if(squad[i] == player_name)
            player_post = i;
    return player_post;
}

vector <string> Match_team::get_mentioned_players(int post1, int post2)
{
    return {squad[post1], squad[post2]};
}

vector <string> Match_team::get_mentioned_players(int post1, int post2, int post3)
{
    return {squad[post1], squad[post2], squad[post3]};
}
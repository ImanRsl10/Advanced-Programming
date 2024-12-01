#include <iostream>

#include "../include/match.hpp"
#include "../include/constants.hpp"

using namespace std;

void Match::add_match_team(vector <Match_team> teams)
{
    host_team = teams[HOST];
    visiting_team = teams[VISITING];
    Teams[HOST] = host_team;
    Teams[VISITING] = visiting_team;
}

vector <int> Match::get_teams_score()
{
    if(host_team.get_gf() > visiting_team.get_gf())
        return {WIN_SCORE, LOOSE_SCORE};
    else if(host_team.get_gf() == visiting_team.get_gf())
        return {DRAW_SCORE, DRAW_SCORE};
    else
        return {LOOSE_SCORE, WIN_SCORE};
}

int Match::check_if_team_played(string team_name)
{
    if(host_team.get_name() == team_name)
        return HOST;
    else if(visiting_team.get_name() == team_name)
        return VISITING;
    else
        return TEAM_NOT_PLAYED;
}

void Match::print_info()
{
    cout << host_team.get_name() << " " << host_team.get_gf() << " | " <<
            visiting_team.get_name() << " " << visiting_team.get_gf() << endl;
}

bool Match::is_player_played(string player_name)
{
    return host_team.is_player_in_squad(player_name) || visiting_team.is_player_in_squad(player_name);
}

int Match::check_team_status(string player_name)
{
    bool player_team = host_team.is_player_in_squad(player_name) ? HOST : VISITING;
    if(Teams[player_team].get_gf() > Teams[!player_team].get_gf())
        return WIN_PLAYER_SCORE;
    else if(Teams[player_team].get_gf() == Teams[!player_team].get_gf())
        return DRAW_PLAYER_SCORE;
    else
        return LOOSE_PLAYER_SCORE;
}

int Match::get_player_team_ga(string player_name)
{
    bool player_team = host_team.is_player_in_squad(player_name) ? HOST : VISITING;
    return get_teams_goals()[!player_team];
}

pair <int, int> Match::get_player_goals_assists(string player_name)
{
    int num_of_goals = INIT;
    int num_of_assists = INIT;
    for(Goal_info goal : goals)
    {
        if(goal.scorer == player_name)
            num_of_goals++;
        else if(goal.assistant == player_name)
            num_of_assists++;
    }
    return make_pair(num_of_goals, num_of_assists);
}

int Match::get_player_own_goals(string player_name)
{
    int num_of_own_goals = INIT;
    for(Goal_info goal : goals)
    {
        if(goal.scorer == player_name)
            if(goal.assistant == OG)
                num_of_own_goals++;
    } 
    return num_of_own_goals;
}

int Match::calc_players_scored_goals(vector <string> mentioned_players)
{
    int num_of_goals = INIT;
    for(string player : mentioned_players)
        num_of_goals += get_player_goals_assists(player).first;
    return num_of_goals;
}

int Match::calc_conceded_goals_score(string player_name) 
{
    int conceded_goals = INIT;
    vector <string> mentioned_players;
    bool player_team = host_team.is_player_in_squad(player_name) ? HOST : VISITING;
    int player_post = Teams[player_team].find_player_post(player_name);
    if(player_post == LB)
    {
        mentioned_players = Teams[!player_team].get_mentioned_players(RF, RB);
        conceded_goals = calc_players_scored_goals(mentioned_players);
    }
    else if(player_post == RB)
    {
        mentioned_players = Teams[!player_team].get_mentioned_players(LF, LB);
        conceded_goals = calc_players_scored_goals(mentioned_players);
    }  
    else if (player_post == (LCB || RCB))
    {
        mentioned_players = Teams[!player_team].get_mentioned_players(CF, LCB, RCB);
        conceded_goals = calc_players_scored_goals(mentioned_players);
    }
    else if(player_post == (LCM || CDM || RCM))
    {
        mentioned_players = Teams[!player_team].get_mentioned_players(LCM, CDM, RCM);
        conceded_goals = calc_players_scored_goals(mentioned_players);
    }
    return conceded_goals;
}
#include <iostream>

#include "constants.hpp"
#include "match.hpp"

using namespace std;

void Match::add_match_team(vector <Match_team> teams)
{
    host_team = teams[HOST];
    visiting_team = teams[VISITING];
}

vector <int> Match::get_teams_score()
{
    if(host_team.GF > visiting_team.GF)
        return {WIN_SCORE, LOOSE_SCORE};
    else if(host_team.GF == visiting_team.GF)
        return {DRAW_SCORE, DRAW_SCORE};
    else
        return {LOOSE_SCORE, WIN_SCORE};
}

int Match::check_if_team_played(string team_name)
{
    if(host_team.name == team_name)
        return HOST;
    else if(visiting_team.name == team_name)
        return VISITING;
    else
        return TEAM_NOT_PLAYED;
}

void Match::print_info()
{
    cout << host_team.name << " " << host_team.GF << " | " <<
            visiting_team.name << " " << visiting_team.GF << endl;
}
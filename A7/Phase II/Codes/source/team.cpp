#include <iostream>
#include <iomanip>
#include <algorithm>

#include "../include/team.hpp"
#include "../include/prim_funcs.hpp"

using namespace std;

void Team::update_status(int match_score, int match_gf, int match_ga)
{
    score += match_score;
    GF += match_gf;
    GA += match_ga;
    GD += match_gf - match_ga;
}

void Team::process_members_info(int current_week, string role, bool rank)
{
    vector <Player*> players;
    if(role != NO_ROLE)
        players = find_players_by_role(role, team_members);
    else   
        players = team_members;
    if(rank)
        sort(players.begin(), players.end(), compare_by_score(current_week));
    else   
        sort(players.begin(), players.end(), compare_players_by_name);

    print_members_info(players, current_week);
}

void Team::print_members_info(vector <Player*> team_members, int current_week)
{
    print_message("list of players:");
    for(int i = 0; i < team_members.size(); i++)
    {
        cout << i + 1 << ". ";
        team_members[i]->print_full_info(current_week);
    }
}

void Team::print_info()
{
    cout << name << ": score: " << score << " | GF: " << GF << " | GA: " << GA << endl;
}
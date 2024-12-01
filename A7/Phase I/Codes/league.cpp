#include <iostream>
#include <algorithm>

#include "league.hpp"
#include "prim_funcs.hpp"

using namespace std;

void League::bind_week(Week* curr_week)
{
    curr_week->get_teams(teams);
    curr_week->get_players(players);
}

void League::update_status(int week_num)
{
    weeks[week_num]->update(week_num);
    arrange_table();
}

bool League::is_a_valid_role(string role)
{
    return role == ROLES[GK] || role == ROLES[DEF] || role == ROLES[MID] ||
           role == ROLES[FORW] || role == NO_ROLE;
}

Team* League::find_team_by_name(string team_name)
{
    for(Team* team : teams)
        if(team->is_name_match(team_name))
            return team;
    return NULL;
}

void League::print_team_info(string team_name, int current_week, string role, bool rank)
{
    Team* mentioned_team = find_team_by_name(team_name);
    if(mentioned_team != NULL)
    {
        if(!is_a_valid_role(role))
            throw BAD_REQUEST;
        mentioned_team->process_members_info(current_week, role, rank);
    }
    else
        throw NOT_FOUND;   
}

void League::arrange_table()
{
    sort(teams.begin(), teams.end(), compare_teams_by_name);
}

void League::print_table()
{
    print_message("league standing:");
    int i = START;
    for(Team* team : teams)
    {
        cout << i << ". ";
        team->print_info();
        i++;
    }
}

pair <Player*, Player*> League::find_best_player(int week_num, string role) //works correct?
{
    vector <Player*> candidates = find_players_by_role(role, players);
    Player* best_player1 = NULL;
    Player* best_player2 = NULL;
    float highest_score = INITIAL_SCORE;

    for(Player* current_player : candidates)
    {
        float player_score = current_player->get_score_of_the_week(week_num);
        if(player_score > highest_score)
        {
            best_player2 = best_player1;
            best_player1 = current_player;
            highest_score = player_score;
        }
        else if(player_score == highest_score)
        {
            if(current_player->get_name() < best_player1->get_name())
            {
                best_player2 = best_player1;
                best_player1 = current_player;
            }
            else if(best_player2 == NULL || current_player->get_name() < best_player2->get_name())
                best_player2 = current_player;
        }
    }
    return make_pair(best_player1, best_player2);
}

void League::print_team_of_the_week(Player* best_GK, Player* best_DEF1, Player* best_DEF2,
                                    Player* best_MID, Player* best_FORW, int week_num)
{
    cout << "GoalKeeper: ";
    best_GK->print_info(week_num);
    cout << "Defender 1: ";
    best_DEF1->print_info(week_num);
    cout << "Defender 2: ";
    best_DEF2->print_info(week_num);
    cout << "Midfielder: ";
    best_MID->print_info(week_num);
    cout << "Forward: ";
    best_FORW->print_info(week_num);
}

void League::determine_team_of_the_week(int week_num)
{
    Player* best_GK = find_best_player(week_num, ROLES[GK]).first;
    pair <Player*, Player*> best_DEFs = find_best_player(week_num, ROLES[DEF]);
    Player* best_MID = find_best_player(week_num, ROLES[MID]).first;
    Player* best_FORW = find_best_player(week_num, ROLES[FORW]).first;

    print_team_of_the_week(best_GK, best_DEFs.first, best_DEFs.second, best_MID, best_FORW, week_num);
}

void League::print_matches_in_week(int week_num)
{
    weeks[week_num]->print_matches();
}

Player* League::find_player_by_name(string player_name)
{
    for(Player* player : players)
        if(player->is_name_match(player_name))
            return player;
    return NULL;
}
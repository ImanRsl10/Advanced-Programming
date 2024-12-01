#include <iostream>

#include "../include/squad.hpp"

using namespace std;

void Squad::add_player(Player* player)
{
    if(player->is_role_match(ROLES[GK]))
    {
        if(!goalkeeper.is_empty())
            throw BAD_REQUEST;
        goalkeeper.set(player);
    }
    else if(player->is_role_match(ROLES[DEF]))
    {
        if(!defender1.is_empty())
        {
            if(!defender2.is_empty())
                throw BAD_REQUEST;
            defender2.set(player);

        }
        else
            defender1.set(player);
    }
    else if(player->is_role_match(ROLES[MID]))
    {
        if(!midfielder.is_empty())
            throw BAD_REQUEST;
        midfielder.set(player);
    }
    else if(player->is_role_match(ROLES[FORW]))
    {
        if(!forward.is_empty())
            throw BAD_REQUEST;
        forward.set(player);
    }
}

void Squad::remove_player(string player_name)
{
    if(!goalkeeper.is_empty() && goalkeeper.is_name_match(player_name))
            goalkeeper.flush();
    else if(!defender1.is_empty() && defender1.is_name_match(player_name))
            defender1.flush();
    else if(!defender2.is_empty() && defender2.is_name_match(player_name))
            defender2.flush();
    else if(!midfielder.is_empty() && midfielder.is_name_match(player_name))
            midfielder.flush();
    else if(!forward.is_empty() && forward.is_name_match(player_name))
            forward.flush();
    else 
        throw NOT_FOUND;
}

void Squad::sort_defenders()
{
    Squad_player temp_player;
    if(defender1.get_name() > defender2.get_name())
    {
        temp_player = defender1;
        defender1 = defender2;
        defender2 = temp_player;
    }
}

void Squad::print()
{
    sort_defenders();
    cout << "Goalkeeper: "; goalkeeper.print_info();
    cout << "Defender1: "; defender1.print_info();
    cout << "Defender2: "; defender2.print_info();
    cout << "Midfielder: "; midfielder.print_info();
    cout << "Striker: "; forward.print_info();
}

bool Squad::is_team_complete()
{
    return !goalkeeper.is_empty() && !defender1.is_empty() && !defender2.is_empty() &&
           !midfielder.is_empty() && !forward.is_empty();
}

float Squad::calc_score_of_week(int current_week)
{
    float score = INIT_TEAM_SCORE;
    score += (!goalkeeper.is_empty()) ? goalkeeper.get_score_of_the_week(current_week) : PLAYER_NOT_PLAYED;
    score += (!defender1.is_empty()) ? defender1.get_score_of_the_week(current_week) : PLAYER_NOT_PLAYED;
    score += (!defender2.is_empty()) ? defender2.get_score_of_the_week(current_week) : PLAYER_NOT_PLAYED;
    score += (!midfielder.is_empty()) ? midfielder.get_score_of_the_week(current_week) : PLAYER_NOT_PLAYED;
    score += (!forward.is_empty()) ? forward.get_score_of_the_week(current_week) : PLAYER_NOT_PLAYED;
    return score;
}

Squad& Squad::operator=(const Squad& squad)
{
    if(this == &squad)
        return *this;
    goalkeeper = squad.goalkeeper;
    defender1 = squad.defender1;
    defender2 = squad.defender2;
    midfielder = squad.midfielder;
    forward = squad.forward;
    return *this;
}

void Squad::set_captain(string player_name)
{
    if(!goalkeeper.is_empty() && goalkeeper.is_name_match(player_name))
        goalkeeper.set_captain();
    else if(!defender1.is_empty() && defender1.is_name_match(player_name))
        defender1.set_captain();
    else if(!defender2.is_empty() && defender2.is_name_match(player_name))
        defender2.set_captain();
    else if(!midfielder.is_empty() && midfielder.is_name_match(player_name))
        midfielder.set_captain();
    else if(!forward.is_empty() && forward.is_name_match(player_name))
        forward.set_captain();
    else
        throw NOT_FOUND;
}

int Squad::calc_total_cost()
{
    int cost = INIT;

    cost += goalkeeper.get_price();
    cost += defender1.get_price();
    cost += defender2.get_price();
    cost += midfielder.get_price();
    cost += forward.get_price();
    
    return cost;
}
#include <iostream>

#include "squad.hpp"

using namespace std;

void Squad::add_player(Player* player)
{
    if(player->has_role(ROLES[GK]))
    {
        if(goalkeeper != NULL)
            throw BAD_REQUEST;
        goalkeeper = player;
    }
    else if(player->has_role(ROLES[DEF]))
    {
        if(defender1 != NULL)
        {
            if(defender2 != NULL)
                throw BAD_REQUEST;
            defender2 = player;
        }
        else
            defender1 = player;
    }
    else if(player->has_role(ROLES[MID]))
    {
        if(midfielder != NULL)
            throw BAD_REQUEST;
        midfielder = player;
    }
    else if(player->has_role(ROLES[FORW]))
    {
        if(forward != NULL)
            throw BAD_REQUEST;
        forward = player;
    }
}

void Squad::remove_player(string player_name)
{
    if(goalkeeper != NULL && goalkeeper->is_name_match(player_name))
            goalkeeper = NULL;
    else if(defender1 != NULL && defender1->is_name_match(player_name))
            defender1 = NULL;
    else if(defender2 != NULL && defender2->is_name_match(player_name))
            defender2 = NULL;
    else if(midfielder != NULL && midfielder->is_name_match(player_name))
            midfielder = NULL;
    else if(forward != NULL && forward->is_name_match(player_name))
            forward = NULL;
    else 
        throw NOT_FOUND;
}

void Squad::sort_defenders()
{
    Player* temp_player = NULL;
    if(defender1->get_name() > defender2->get_name())
    {
        temp_player = defender1;
        defender1 = defender2;
        defender2 = temp_player;
    }
}

void Squad::print()
{
    sort_defenders();
    cout << "Goalkeeper: " << goalkeeper->get_name() << endl;
    cout << "Defender1: " << defender1->get_name() << endl;
    cout << "Defender2: " << defender2->get_name() << endl;
    cout << "Midfielder: " << midfielder->get_name() << endl;
    cout << "Striker: " << forward->get_name() << endl;
}

float Squad::calc_score_of_week(int current_week)
{
    float score = INIT_TEAM_SCORE;
    score += (goalkeeper != NULL) ? goalkeeper->get_score_of_the_week(current_week) : PLAYER_NOT_PLAYED;
    score += (defender1 != NULL) ? defender1->get_score_of_the_week(current_week) : PLAYER_NOT_PLAYED;
    score += (defender2 != NULL) ? defender2->get_score_of_the_week(current_week) : PLAYER_NOT_PLAYED;
    score += (midfielder != NULL) ? midfielder->get_score_of_the_week(current_week) : PLAYER_NOT_PLAYED;
    score += (forward != NULL) ? forward->get_score_of_the_week(current_week) : PLAYER_NOT_PLAYED;
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
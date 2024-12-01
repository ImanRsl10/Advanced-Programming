#include <iostream>
#include <iomanip>

#include "../include/forward.hpp"

using namespace std;

void Forward::calc_raw_score(int current_week)
{
    int raw_score = INIT, scored_goals = INIT, assitants = INIT;

    if(matches[current_week] != NULL)
    {
        auto [scored_goals, assitants] = matches[current_week]->get_player_goals_assists(name);

        raw_score += matches[current_week]->check_team_status(name);
        raw_score += (scored_goals) ? FORW_GOAL_SCORE * scored_goals : FORW_NOT_SCORING_SCORE;
        raw_score += FORW_ASSIST_SCORE * matches[current_week]->get_player_goals_assists(name).second; 

        raw_score += OG_SCORE * matches[current_week]->get_player_own_goals(name);
    }
    num_of_goals += scored_goals;
    num_of_assists += assitants;
    raw_scores[current_week] = raw_score;
}

void Forward::print_full_info(int current_week)
{
    cout << "name: " << name << " | role: " << ROLES[FORW] << " | score: " <<
    fixed << setprecision(1) << calc_mean_score(current_week) << " | cost: N/A" <<
    " | goals: " << num_of_goals << " | assists: " << num_of_assists << endl;
}
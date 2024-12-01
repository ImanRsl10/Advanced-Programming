#include <iostream>
#include <iomanip>

#include "../include/goal_keeper.hpp"

using namespace std;

void Goalkeeper::calc_raw_score(int current_week)
{
    int raw_score = INIT, conceded_goals = INIT;

    if(matches[current_week] != NULL)
    {
        conceded_goals = matches[current_week]->get_player_team_ga(name);

        raw_score += INIT_GK_SCORE;
        raw_score += matches[current_week]->check_team_status(name);

        raw_score += (conceded_goals) ? CONCEDED_GOAL_SCORE * conceded_goals : GK_CLEAN_SHEET_SCORE;
        raw_score += OG_SCORE * matches[current_week]->get_player_own_goals(name);
        
        update_clean_sheet(conceded_goals);
    }
    raw_scores[current_week] = raw_score;
}

void Goalkeeper::print_full_info(int current_week)
{
    cout << "name: " << name << " | role: " << ROLES[GK] << " | score: " <<
    fixed << setprecision(1) << calc_mean_score(current_week) << " | cost: N/A" <<
    " | clean sheets: " << num_of_clean_sheets << endl;
}
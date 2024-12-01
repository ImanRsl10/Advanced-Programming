#include <iostream>
#include <iomanip>

#include "../include/midfielder.hpp"

using namespace std;

void Midfielder::calc_raw_score(int current_week)
{
    int raw_score = INIT, scored_goals = INIT, assistants = INIT, conceded_goals = INIT;

    if(matches[current_week] != NULL)
    {
        conceded_goals = matches[current_week]->get_player_team_ga(name);
        auto [scored_goals, assitants] = matches[current_week]->get_player_goals_assists(name);

        raw_score += matches[current_week]->check_team_status(name);
        raw_score += MID_GOAL_SCORE * scored_goals;
        raw_score += MID_ASSIST_SCORE * assistants;

        raw_score += (conceded_goals) ? CONCEDED : MID_CLEAN_SHEET_SCORE;
        raw_score += OG_SCORE * matches[current_week]->get_player_own_goals(name);
        raw_score += OPPONENT_SCORED_SCORE * matches[current_week]->calc_conceded_goals_score(name);

        update_clean_sheet(conceded_goals);
    }
    num_of_goals += scored_goals;
    num_of_assists += assistants;
    raw_scores[current_week] = raw_score;
}

void Midfielder::print_full_info(int current_week)
{
    cout << "name: " << name << " | role: " << ROLES[MID] << " | score: " <<
    fixed << setprecision(1) << calc_mean_score(current_week) << " | cost: N/A" <<
    " | goals: " << num_of_goals << " | assists: " << num_of_assists <<
    " | clean sheets: " << num_of_clean_sheets << endl;
}
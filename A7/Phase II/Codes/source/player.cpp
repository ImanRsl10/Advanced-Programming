#include <iostream>
#include <iomanip>

using namespace std;

#include "../include/player.hpp"
#include "../include/prim_funcs.hpp"

void Player::check_suspension(int next_week, bool got_yellow_card, bool got_red_card)
{
    if(got_yellow_card)
        yellow_cards++;
    if(yellow_cards == SUSPENSION_THRESHOLD)
    {
        weeks_stats[next_week].suspended = true;
        yellow_cards = INIT;
    }
    else if(got_red_card)
    {
        weeks_stats[next_week].suspended = true;
        yellow_cards = INIT;
    }
}

void Player::check_injury_status(int next_week)
{
    weeks_stats[next_week].injured = true;
    if(next_week + 1 < NUM_OF_WEEKS)
        weeks_stats[next_week + 1].injured = true;
    if(next_week + 2 < NUM_OF_WEEKS)
        weeks_stats[next_week + 2].injured = true;
}

void Player::update_status(int this_week, bool injured, bool got_yellow_card, bool got_red_card)
{
    int next_week = this_week + 1;
    if(next_week < NUM_OF_WEEKS)
    {
        check_suspension(next_week, got_yellow_card, got_red_card);
        if(injured)
            check_injury_status(next_week);
    }
    calc_raw_score(this_week);
    calc_score(this_week);
}

float Player::get_score_of_the_week(int current_week, bool is_captain)
{
    float score = INITIAL_SCORE;
    if(is_captain)
    {
        float cap_raw_score = DOUBLE * raw_scores[current_week];
        score = calc_Ax(cap_raw_score);
    }
    else
        score = weeks_scores[current_week];
    return score;
}

float Player::calc_total_score(int week_num, int& num_of_matches_played)
{
    num_of_matches_played = INIT;
    float score = PLAYER_NOT_PLAYED;

    for(int i = 0; i <= week_num; i++)
    {
        if(weeks_scores[i] != PLAYER_NOT_PLAYED)
        {
            num_of_matches_played++;
            score += weeks_scores[i];
        }    
    }
    return score;
}

float Player::calc_mean_score(int week_num)
{
    int num_of_matches_played;
    float total_score = calc_total_score(week_num, num_of_matches_played);
    if(num_of_matches_played == 0)
        return PLAYER_NOT_PLAYED;
    else
        return total_score / num_of_matches_played;
}

void Player::print_info(int week_num)
{
    cout << "name: " << name << " | score: ";
    cout << fixed << setprecision(1) << weeks_scores[week_num] << endl;
}

void Player::calc_score(int current_week)
{
    int raw_score = raw_scores[current_week];
    weeks_scores[current_week] = (raw_score) ? calc_Ax(raw_score) : PLAYER_NOT_PLAYED;
}
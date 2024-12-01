#include <iostream>
#include <iomanip>

#include "constants.hpp"
#include "player.hpp"

using namespace std;

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

void Player::update_status(int this_week, bool injured, bool got_yellow_card,
                           bool got_red_card, float score)
{
    int next_week = this_week + 1;
    weeks_stats[this_week].score = score;
    if(next_week < NUM_OF_WEEKS)
    {
        check_suspension(next_week, got_yellow_card, got_red_card);
        if(injured)
            check_injury_status(next_week);
    }
}

float Player::calc_score_in_interval(int modified_week, int current_week)
{
    int num_of_matches_played = INIT;
    float score = PLAYER_NOT_PLAYED;

    for(int i = modified_week; i <= current_week; i++)
    {
        if(weeks_stats[i].score != PLAYER_NOT_PLAYED)
        {
            num_of_matches_played++;
            score += weeks_stats[i].score;
        }    
    }
    if(num_of_matches_played == 0)
        return PLAYER_NOT_PLAYED;
    return score;
}

float Player::calc_total_score(int week_num, int& num_of_matches_played)
{
    num_of_matches_played = INIT;
    float score = PLAYER_NOT_PLAYED;

    for(int i = 0; i <= week_num; i++)
    {
        if(weeks_stats[i].score != PLAYER_NOT_PLAYED)
        {
            num_of_matches_played++;
            score += weeks_stats[i].score;
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
    cout << fixed << setprecision(1) << weeks_stats[week_num].score << endl;
}

void Player::print_info(int week_num, bool mode)
{
    cout << "name: " << name << " | role: " << role << " | score: ";
    cout << fixed << setprecision(1) << calc_mean_score(week_num) << endl;
}
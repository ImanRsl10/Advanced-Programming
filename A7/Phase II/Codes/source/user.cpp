#include <iostream>
#include <iomanip>

#include "../include/user.hpp"

using namespace std;

User::User(std::string username, std::string pass) : squad(), submiited_squad()
{
    fantasy_team_name = username;
    password = pass;
    score = INIT_TEAM_SCORE;
    team_is_complete = false;
    num_of_transfers = INIT;
    budget = INIT_BUDGET;
}

void User::buy_player(Player* player)
{
    if(budget < player->get_price())
        throw BAD_REQUEST;
    squad.add_player(player);
    budget -= player->get_price();
}

void User::sell_player(Player* player)
{
    squad.remove_player(player->get_name());
    budget += player->get_price();
}

void User::print_squad()
{
    if(!team_is_complete || !submiited_squad.is_team_complete())
        throw EMPTY;
    cout << "fantasy_team: " << fantasy_team_name << endl;
    submiited_squad.print();
    cout << "Total Points: " << fixed << setprecision(1) << score << endl;
    cout << "Total Cost: " << submiited_squad.calc_total_cost() << endl;
}

void User::check_if_team_is_complete(int current_week)
{
    if(squad.is_team_complete())
        team_is_complete = true;
}

void User::update_score(int current_week)
{
    score += squad.calc_score_of_week(current_week);
}

void User::print_info()
{
    cout << "team_name: " << fantasy_team_name << " | point: " << score << endl;
}
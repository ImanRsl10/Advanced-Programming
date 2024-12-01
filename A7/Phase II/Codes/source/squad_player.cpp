#include <iostream>

#include "../include/squad_player.hpp"

using namespace std;

float Squad_player::get_score_of_the_week(int current_week)
{
    return player->get_score_of_the_week(current_week, captain);
}

void Squad_player::print_info()
{
    cout << player->get_name();
    if(captain)
        cout << SPACE + CAPTAIN << endl;
    else
        cout << endl;
}
#include "constants.hpp"
#include "week.hpp"

using namespace std;

void Week::set_info(vector <string> injuries, vector <string> yellow_cards, 
                         vector <string> red_cards, vector <Player_score> players_scores)
{
    this->injuries.insert(this->injuries.end(), injuries.begin(), injuries.end());
    this->yellow_cards.insert(this->yellow_cards.end(), yellow_cards.begin(), yellow_cards.end());
    this->red_cards.insert(this->red_cards.end(), red_cards.begin(), red_cards.end());
    this->players_scores.insert(this->players_scores.end(), players_scores.begin(), players_scores.end());
}

float Week::get_player_score(Player* current_player)
{
    for(Player_score player : players_scores)
        if(current_player->is_name_match(player.name))
            return player.score;
    return PLAYER_NOT_PLAYED;
}

bool Week::check_if_mentioned(Player* current_player, vector <string> mentioned_players)
{
    for(string player : mentioned_players)
        if(current_player->is_name_match(player))
            return true;
    return false;
}

void Week::update_players_status(int week_num)
{
    for(Player* player : players)
    {
        bool injured = check_if_mentioned(player, injuries);
        bool got_yellow_card = check_if_mentioned(player, yellow_cards);
        bool got_red_card = check_if_mentioned(player, red_cards);
        float score = get_player_score(player);

        player->update_status(week_num, injured, got_yellow_card, got_red_card, score);
    }
}

void Week::find_match_team_played(string team_name, int& team_score, int& gf, int& ga)
{
    for(Match match : mathces)
    {
        int index = match.check_if_team_played(team_name);
        if(index != TEAM_NOT_PLAYED)
        {
            team_score = match.get_teams_score()[index];
            gf = match.get_teams_goals()[index];
            ga = match.get_teams_goals()[!index];
            return;
        }
    }
}

void Week::update_teams_status()
{
    for(Team* team : teams)
    {
        int match_score, gf, ga;
        find_match_team_played(team->get_name(), match_score, gf, ga); 
        team->update_status(match_score, gf, ga); 
    }
}

void Week::update(int week_num)
{
    update_players_status(week_num);
    update_teams_status();
}

void Week::print_matches()
{
    for(Match match : mathces)
        match.print_info();
}
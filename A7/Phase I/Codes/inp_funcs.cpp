#include <algorithm>

#include "constants.hpp"
#include "inp_funcs.hpp"
#include "prim_funcs.hpp"

using namespace std;

vector <string> read_csv(string filename)
{
    ifstream input_csv(filename);
    string line;
    vector <string> data;

    getline(input_csv, line);
    while (getline(input_csv, line))
        data.push_back(line);

    input_csv.close();
    return data;
}

void add_player(League* league, Team* team, vector <string> players, string role)
{
    for(string player_name : players)
    {
        Player* new_player = new Player(player_name, role);
        league->add_player(new_player);
        team->add_team_member(new_player);
    }
}

void assign_data(League* league, vector <string> seperated_line)
{
    string team_name = seperated_line[0];

    vector <string> goal_keepers = split_by_identifire(seperated_line[1], SEMI_COLON);
    vector <string> defenders = split_by_identifire(seperated_line[2], SEMI_COLON);
    vector <string> midfielders = split_by_identifire(seperated_line[3], SEMI_COLON);
    vector <string> forwards = split_by_identifire(seperated_line[4], SEMI_COLON);

    forwards.back().erase(remove(forwards.back().begin(), forwards.back().end(), '\r'), forwards.back().end());

    vector <vector <string> > players = {goal_keepers, defenders, midfielders, forwards};

    Team* new_team = new Team(team_name);
    league->add_team(new_team);

    for(int i = 0; i < NUM_OF_ROLES; i++)
        add_player(league, new_team, players[i], ROLES[i]);
}

void assign_data(Week* week, vector <string> seperated_line)
{
    vector <string> match_teams_names = split_by_identifire(seperated_line[0], COLON);
    vector <string> match_teams_goals = split_by_identifire(seperated_line[1], COLON);
    vector <string> injuries = split_by_identifire(seperated_line[2], SEMI_COLON);
    vector <string> yellow_cards = split_by_identifire(seperated_line[3], SEMI_COLON);
    vector <string> red_cards = split_by_identifire(seperated_line[4], SEMI_COLON);
    vector <string> players_scores_mixed = split_by_identifire(seperated_line[5], SEMI_COLON);

    players_scores_mixed.back().erase(remove(players_scores_mixed.back().begin(), players_scores_mixed.back().end(),'\r'), 
                                players_scores_mixed.back().end());

    Match match = handle_match_info(match_teams_names, match_teams_goals);
    vector <Player_score> players_scores = handle_player_scores_info(players_scores_mixed);
    
    week->set_info(injuries, yellow_cards, red_cards, players_scores);
    week->add_match(match);
}

Match handle_match_info(vector <string> match_teams_names, vector <string> match_teams_goals)
{
    Match match;
    vector <Match_team> teams(NUM_OF_MATCH_TEAMS);
    
    for(int i = 0; i < NUM_OF_MATCH_TEAMS; i++)
        teams[i] = Match_team(match_teams_names[i], stoi(match_teams_goals[i]));
    match.add_match_team(teams);
    return match;
}

vector <Player_score> handle_player_scores_info(vector <string> players_scores_mixed)
{
    vector <Player_score> players_scores;
    for(string player_score : players_scores_mixed)
    {
        vector <string> score_info = split_by_identifire(player_score, COLON);
        players_scores.push_back({score_info[0], stof(score_info[1])});
    }
    return players_scores;
}
#include <algorithm>

#include "../include/inp_funcs.hpp"
#include "../include/prim_funcs.hpp"
#include "../include/goal_keeper.hpp"
#include "../include/defender.hpp"
#include "../include/midfielder.hpp"
#include "../include/forward.hpp"

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

pair <string, int> extract_player_info(string player_info)
{
    string name = split_by_identifire(player_info, COLON)[0];
    string price = split_by_identifire(player_info, COLON)[1];

    return make_pair(name, stoi(price));
}

void add_player(League* league, Team* team, vector <string> players, string role)
{
    string player_name;
    int player_price = INIT;
    Player* new_player;
    for(string player_info : players)
    {
        auto [player_name, player_price] = extract_player_info(player_info);
        if(role == ROLES[GK])
            new_player = new Goalkeeper(player_name, player_price);
        else if(role == ROLES[DEF])
            new_player = new Defender(player_name, player_price);
        else if(role == ROLES[MID])
            new_player = new Midfielder(player_name, player_price);
        else if(role == ROLES[FORW])
            new_player = new Forward(player_name, player_price);
        //correct ?
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

Match handle_match_info(vector <string> match_teams_names, vector <string> match_teams_goals,
                        vector <string> host_squad, vector <string> visiting_team, vector <Goal_info> goals)
{
    Match match;
    vector <Match_team> teams(NUM_OF_MATCH_TEAMS);

    teams[0] = Match_team(match_teams_names[0], stoi(match_teams_goals[0]), host_squad);
    teams[1] = Match_team(match_teams_names[1], stoi(match_teams_goals[1]), visiting_team);

    match.add_match_team(teams);
    match.set_goals(goals);
    return match;
}

vector <Goal_info> handle_goals_info(vector <string> goals_assists_info)
{
    vector <Goal_info> goals;
    for(string goal : goals_assists_info)
    {
        vector <string> goal_info = split_by_identifire(goal, COLON);
        goals.push_back({goal_info[0], goal_info[1]});
    }
    return goals;
}

void assign_data(Week* week, vector <string> seperated_line)
{
    vector <string> match_teams_names = split_by_identifire(seperated_line[0], COLON);
    vector <string> match_teams_goals = split_by_identifire(seperated_line[1], COLON);
    vector <string> injuries = split_by_identifire(seperated_line[2], SEMI_COLON);
    vector <string> yellow_cards = split_by_identifire(seperated_line[3], SEMI_COLON);
    vector <string> red_cards = split_by_identifire(seperated_line[4], SEMI_COLON);
    vector <string> goals_assists_info = split_by_identifire(seperated_line[5], SEMI_COLON);
    vector <string> host_team_squad = split_by_identifire(seperated_line[6], SEMI_COLON);
    vector <string> visiting_team_squad = split_by_identifire(seperated_line[7], SEMI_COLON);

    visiting_team_squad.back().erase(remove(visiting_team_squad.back().begin(), visiting_team_squad.back().end(),'\r'), 
                                     visiting_team_squad.back().end());

    vector <Goal_info> goals = handle_goals_info(goals_assists_info);
    Match match = handle_match_info(match_teams_names, match_teams_goals, host_team_squad,
                                    visiting_team_squad, goals);
    week->set_info(injuries, yellow_cards, red_cards);
    week->add_match(match);
}

bool is_valid_cmd(string command, const string identifire1, const string identifire2,
                  const string identifire3, const string identifire4)
{
    return command == identifire1 || command == identifire2 || command == identifire3 ||
           command == identifire4;
}

bool is_valid_cmd(string command, const string identifire1, const string identifire2,
                  const string identifire3, const string identifire4, const string identifire5,
                  const string identifire6, const string identifire7)
{
    return command == identifire1 || command == identifire2 || command == identifire3 ||
           command == identifire4 || command == identifire5 || command == identifire6 ||
           command == identifire7;
}

bool is_valid_cmd(string command, const string identifire1, const string identifire2,
                  const string identifire3, const string identifire4, const string identifire5,
                  const string identifire6, const string identifire7, const string identifire8,
                  const string identifire9, const string identifire10)
{
    return command == identifire1 || command == identifire2 || command == identifire3 ||
           command == identifire4 || command == identifire5 || command == identifire6 ||
           command == identifire7 || command == identifire8 || command == identifire9 ||
           command == identifire10;
}
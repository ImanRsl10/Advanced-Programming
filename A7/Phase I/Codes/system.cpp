#include <iostream>
#include <algorithm>

#include "system.hpp"
#include "prim_funcs.hpp"
#include "inp_funcs.hpp"

using namespace std;

System::System() : admin()
{
    current_user = NULL;
    current_week = INIT;
    last_week = INIT_WEEK;
    admin_logged = false;
    user_logged = false;
    transfer_window_status = OPEN;
    league = new League();
    set_teams_players_data(PREMIER_LEAGUE_CSV);
    set_weeks_stats(WEEK);
}

void System::set_teams_players_data(string filename)
{
    vector <string> data, seperated_line;
    data = read_csv(filename);

    for(string data_line : data)
    {
        seperated_line = split_by_identifire(data_line, COMMA);
        assign_data(league, seperated_line);
    }
}

void System::set_weeks_stats(string filename_pattern)
{
    vector <string> data, seperated_line;
    for(int i = FIRST_WEEK; i <= NUM_OF_WEEKS; i++)
    {
        Week* curr_week = new Week();
        string filename = filename_pattern + to_string(i) + CSV;
        data = read_csv(filename);
        for(string data_line : data)
        {
            seperated_line = split_by_identifire(data_line, COMMA);
            assign_data(curr_week, seperated_line);
        }
        league->add_week(curr_week);
        league->bind_week(curr_week);
    }
}

int System::get_week_number(vector <string> command_details)
{
    int week_num = last_week;
    if(command_details.size() == 5)
        week_num = stoi(command_details.back()) - 1;
    if(!is_in_weeks(week_num))
        throw BAD_REQUEST;
    return week_num;
}

void System::handle_GET_commands(vector <string> command_details)
{
    string command = command_details[1];
    if(!is_valid_cmd(command, TOTW, PLAYERS, STANDING, USERS_RANKING, MATCHES_IN_WEEK, SQUAD))
        throw BAD_REQUEST;
    else if(command == TOTW)
        handle_TOTW_command(command_details);
    else if(command == PLAYERS)
        handle_players_command(command_details);
    else if(command == STANDING)
        league->print_table();
    else if (command == USERS_RANKING)
        show_users_ranking();
    else if(command == MATCHES_IN_WEEK)
        handle_matches_command(command_details);
    else if(command == SQUAD)
        show_user_squad(command_details);
}

void System::handle_TOTW_command(vector <string> command_details)
{
    int week_num = get_week_number(command_details);
    league->determine_team_of_the_week(week_num);
}

void System::handle_players_command(vector <string> command_details)
{
    string role = NO_ROLE;
    bool rank = NO_RANKING;
    vector <string> splitted_team_name = split_by_identifire(command_details[4], UNDERLINE);
    string team_name = assemble_name(splitted_team_name);

    if(command_details.size() == 7)
    {
        role = command_details[5];
        rank = RANKING;
    }
    else if(command_details.size() == 6)
    {
        if(command_details[5] == RANKS)
            rank = RANKING;
        else
            role = command_details[5];
    }

    league->print_team_info(team_name, last_week, role, rank);
}

void System::show_users_ranking()
{
    sort(users.begin(), users.end(), compare_users);
    int i = START;
    for(User* user : users)
    {
        cout << i << ".";
        user->print_info();
        i++;
    }
}

void System::handle_matches_command(vector <string> command_details)
{
    int week_num = get_week_number(command_details);
    league->print_matches_in_week(week_num);
}

void System::show_user_squad(vector <string> command_details)
{
    if(admin_logged || !user_logged)
        throw BAD_REQUEST;
    
    User* mentioned_user = current_user;
    if(command_details.size() == 5)
        mentioned_user = find_user(command_details[4]);
    if(mentioned_user == NULL)
        throw NOT_FOUND;
    mentioned_user->print_squad();
}

void System::handle_POST_commands(vector <string> command_details)
{
    string command = command_details[1];
    if(!is_valid_cmd(command, SIGNUP, LOGIN, REGISTER_ADMIN, LOGOUT, SELL, BUY,
                     CLOSE_TRANSFER_WINDOW, OPEN_TRANSFER_WINDOW, PASS_WEEK))
        throw BAD_REQUEST;
    else if(command == SIGNUP)
        handle_user_signup(command_details);
    else if (command == LOGIN)
        handle_user_login(command_details);
    else if(command == BUY)
        handle_buy_player(command_details);
    else if(command == SELL)
        handle_sell_player(command_details);
    else if(command == REGISTER_ADMIN)
        verify_admin(command_details);
    else if(command == PASS_WEEK)
        handle_pass_week();
    else if(command == OPEN_TRANSFER_WINDOW)
        handle_transfer_window(OPEN);
    else if(command == CLOSE_TRANSFER_WINDOW)
        handle_transfer_window(CLOSED);
    else if(command == LOGOUT)
        handle_logout();
}

bool System::is_duplicate_username(string username)
{
    for(User* user : users)
        if(user->has_same_name(username))
            return true;
    return false;
}

User* System::find_user(string username, string password)
{
    for(User* user : users)
    {
        if(user->is_same_user_name(username))
        {
            if(!user->is_same_password(password))
                throw PERMISSION_DENIED;
            return user;
        }
    }
    return NULL;
}

User* System::find_user(string username)
{
    for(User* user : users)
        if(user->is_same_user_name(username))
            return user;
    return NULL;
}

void System::check_users_status()
{
    for(User* user : users)
    {
        if(user->is_team_complete())
        {
            user->reset_transfer();
            user->update_score(last_week);
        }
        else
            user->check_if_team_is_complete(current_week);
        user->update_squad();
    }
}

void System::handle_user_signup(vector <string> command_details)
{
    if(user_logged || admin_logged)
        throw BAD_REQUEST;

    string username = command_details[4];
    string password = command_details[6];

    if(is_duplicate_username(username))
        throw BAD_REQUEST;

    User* new_user = new User(username, password);
    add_user(new_user);
    current_user = new_user;
    user_logged = true;
    print_message(OK);
}

void System::handle_user_login(vector <string> command_details)
{
    if(user_logged || admin_logged)
        throw BAD_REQUEST;

    string username = command_details[4];
    string password = command_details[6];

    current_user = find_user(username, password);
    if(current_user == NULL)
        throw NOT_FOUND;
    user_logged = true;
    print_message(OK);
}


void System::handle_buy_player(vector <string> command_details)
{
    if(admin_logged || !user_logged)
        throw BAD_REQUEST;
    if(transfer_window_status == CLOSED)
        throw PERMISSION_DENIED;
    
    string player_name = assemble_name({command_details.begin() + 4, command_details.end()});
    Player* mentioned_player = league->find_player_by_name(player_name);

    if(mentioned_player == NULL)
        throw NOT_FOUND;
    if(!mentioned_player->is_available(current_week))
        throw PLAYER_NOT_AVAILABLE;
    if(current_user->is_transfers_complete())
        throw PERMISSION_DENIED + "::You have 2 trnasfers per week"; //test
    
    current_user->buy_player(mentioned_player);

    if(current_user->is_team_complete())
        current_user->set_transfer();
    print_message(OK);
}

void System::handle_sell_player(vector <string> command_details)
{
    if(admin_logged || !user_logged)
        throw BAD_REQUEST;
    if(transfer_window_status == CLOSED)
        throw PERMISSION_DENIED;
    if(current_user->is_transfers_complete())
        throw PERMISSION_DENIED + "::You have 2 trnasfers per week"; //test
    
    string player_name = assemble_name({command_details.begin() + 4, command_details.end()});
    current_user->sell_player(player_name);

    if(current_user->is_team_complete())
        current_user->set_transfer();
    print_message(OK);
}

void System::verify_admin(vector <string> command_details)
{
    if(user_logged || admin_logged)
        throw BAD_REQUEST;

    string username = command_details[4];
    string password = command_details[6];

    if(!admin.is_same_user_name(username) || !admin.is_same_password(password))
        throw BAD_REQUEST;

    admin_logged = true;
    print_message(OK);
}

void System::handle_pass_week()
{
    if(!admin_logged)
        throw PERMISSION_DENIED;

    league->update_status(current_week);
    check_users_status();
    last_week = current_week;
    current_week++;
    print_message(OK);
}

void System::handle_transfer_window(bool status)
{
    if(!admin_logged)
        throw PERMISSION_DENIED;
    transfer_window_status = status;
    print_message(OK);
}

void System::handle_logout()
{
    if(admin_logged)
        admin_logged = false;
    else if(user_logged)
    {
        user_logged = false;
        current_user = NULL;
    }
    else
        throw PERMISSION_DENIED;
    print_message(OK);
}

void System::process_commands()
{
    string line, command_type;
    vector <string> command_line;
    while (getline(cin, line))
    {
        command_line = split_by_identifire(line, SPACE);
        command_type = command_line[0];
        try
        {
            if(!is_valid_cmd(command_type, GET, POST, PUT, DELETE))
                throw BAD_REQUEST;
            else if(command_type == GET)
                handle_GET_commands(command_line);
            else if(command_type == POST)
                handle_POST_commands(command_line);
        }
        catch(const string& error_message)
        {
            print_message(error_message);
        }
    }
}

void System::start()
{
    process_commands();
}
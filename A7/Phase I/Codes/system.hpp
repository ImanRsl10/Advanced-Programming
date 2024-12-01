#pragma once

#include "constants.hpp"
#include "admin.hpp"
#include "league.hpp"
#include "user.hpp"

class System {
public:
    System();
    void start();
private:
    void set_teams_players_data(std::string file_name);
    void set_weeks_stats(std::string filename_pattern);
    bool is_in_weeks(int week_num) { return week_num > INIT_WEEK && week_num <= current_week; }
    int get_week_number(std::vector <std::string> command_details);
    bool is_duplicate_username(std::string username);
    void add_user(User* new_user) { users.push_back(new_user); }
    User* find_user(std::string username, std::string password);
    User* find_user(std::string username);
    void check_users_status();
    void process_commands();
    void handle_GET_commands(std::vector <std::string> command_details);
    void handle_TOTW_command(std::vector <std::string> command_details);
    void handle_players_command(std::vector <std::string> command_details);
    void show_users_ranking();
    void handle_matches_command(std::vector <std::string> command_details);
    void show_user_squad(std::vector <std::string> command_details);
    void handle_POST_commands(std::vector <std::string> command_details);
    void handle_user_login(std::vector <std::string> command_details);
    void handle_user_signup(std::vector <std::string> command_details);
    void handle_buy_player(std::vector <std::string> command_details);
    void handle_sell_player(std::vector <std::string> command_details);
    void verify_admin(std::vector <std::string> command_details);
    void handle_pass_week();    
    void handle_transfer_window(bool status);   
    void handle_logout(); 
private:
    League* league;
    Admin admin;
    std::vector <User*> users;
    User* current_user;
    int current_week;
    int last_week;
    bool admin_logged;
    bool user_logged;
    bool transfer_window_status;
};
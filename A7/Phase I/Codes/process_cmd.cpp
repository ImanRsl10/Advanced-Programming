#include <iostream>

#include "constants.hpp"
#include "process_cmd.hpp"
#include "prim_funcs.hpp"

using namespace std;

void process_command(League& league)
{
    string command;
    int week_num = INIT_WEEK;
    while(cin >> command)
    {
        if(command == "Pass_week")
        {
            week_num++;
            league.update_status(week_num);
            print_message(OK);
        }
        else if(command == TOTW)
        {
            int week_mus;
            cin >> week_mus;
            week_mus--;
            if(week_mus <= week_num)
                league.determine_team_of_the_week(week_mus);
            else
                print_message(BAD_REQUEST);
        }
        else if(command == PLAYERS)
        {
            string team_name, role, rank;
            cin >> team_name >> role >> rank;
            league.print_team_info(team_name, week_num, role, RANKING);
        }
        else if (command == STANDING)
        {
            league.print_table();
        }       
        else if(command == MATCHES_IN_WEEK)
        {
            int week_mud;
            cin >> week_mud;
            week_mud--;
            if(week_mud <= week_num)
                league.print_matches_in_week(week_mud);
            else
                print_message(BAD_REQUEST);
        } 
        else
            print_message(BAD_REQUEST);
    }
}
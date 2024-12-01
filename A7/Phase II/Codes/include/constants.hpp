#pragma once

#include <string>

const std::string PREMIER_LEAGUE_CSV = "input_files/premier_league.csv";
const std::string WEEK = "input_files/weeks_stats/week_";
const std::string CSV = ".csv";

const std::string POST = "POST";
const std::string GET = "GET";
const std::string PUT = "PUT";
const std::string DELETE = "DELETE";

const std::string TOTW = "team_of_the_week";
const std::string PLAYERS = "players";
const std::string STANDING = "league_standings";
const std::string USERS_RANKING = "users_ranking";
const std::string MATCHES_IN_WEEK = "matches_result_league";

const std::string SIGNUP = "signup";
const std::string LOGIN = "login";
const std::string LOGOUT = "logout";
const std::string REGISTER_ADMIN = "register_admin";

const std::string SELL = "sell_player";
const std::string BUY = "buy_player";
const std::string SQUAD = "squad";
const std::string SHOW_BUDGET = "show_budget";
const std::string SET_CAP = "set_captain";

const std::string CLOSE_TRANSFER_WINDOW = "close_transfer_window";
const std::string OPEN_TRANSFER_WINDOW = "open_transfer_window";
const std::string PASS_WEEK = "pass_week";

const std::string OK = "OK";
const std::string BAD_REQUEST = "Bad Request";
const std::string NOT_FOUND = "Not Found";
const std::string PERMISSION_DENIED = "Permission Denied";
const std::string PLAYER_NOT_AVAILABLE = "This player is not available for next week";
const std::string EMPTY = "Empty";

const std::string NOT_PLAYED_SCORE = "0.0"; 
const std::string NO_ROLE = "NO_ROLE";
const std::string RANKS = "ranks";

const std::string ADMIN_USERNAME = "admin";
const std::string ADMIN_PASSWORD = "123456";

const std::string CAPTAIN = "(CAPTAIN)";

const std::string OG = "OWN_GOAL";

const char COMMA = ',';
const char SEMI_COLON = ';';
const char COLON = ':';
const char SPACE = ' ';
const char UNDERLINE = '_';

const std::string ROLES[4] = {"gk", "df", "md", "fw"};

enum roles {GK, DEF, MID, FORW};
enum posts {GLK, LB, LCB, RCB, RB, LCM, CDM, RCM, LF, CF, RF};

const int INIT = 0;
const int INIT_WEEK = -1;
const int FIRST_WEEK = 1;
const int NUM_OF_WEEKS = 19;

const int NUM_OF_MATCH_TEAMS = 2;
const int SUSPENSION_THRESHOLD = 3;

const int WIN_SCORE = 3;
const int LOOSE_SCORE = 0;
const int DRAW_SCORE = 1;

const int HOST = 0;
const int VISITING = 1;

const int TEAM_NOT_PLAYED = -1;
const int NUM_OF_ROLES = 4;

const int FANTASY_TEAM_SIZE = 5;
const int NUM_OF_TRANSFERS = 2;
const int START = 1;

const int INIT_BUDGET = 2500;
const int NUM_OF_PLAYERS_IN_SQUAD = 11;

const int WIN_PLAYER_SCORE = 5;
const int DRAW_PLAYER_SCORE = 1;
const int LOOSE_PLAYER_SCORE = -1;

const int INIT_GK_SCORE = 3;
const int INIT_DEF_SCORE = 1;

const int GK_CLEAN_SHEET_SCORE = 5;
const int DEF_CLEAN_SHEET_SCORE = 2;
const int MID_CLEAN_SHEET_SCORE = 1;

const int DEF_GOAL_SCORE = 4;
const int MID_GOAL_SCORE = 3;
const int FORW_GOAL_SCORE = 3;

const int DEF_ASSIST_SCORE = 3;
const int MID_ASSIST_SCORE = 2;
const int FORW_ASSIST_SCORE = 1;

const int FORW_NOT_SCORING_SCORE = -1;
const int CONCEDED_GOAL_SCORE = -1;
const int OG_SCORE = -3;
const int OPPONENT_SCORED_SCORE = -1;

const float PLAYER_NOT_PLAYED = 0.0;
const float INIT_TEAM_SCORE = 0.0;
const float INITIAL_SCORE = -1.0;

const float DOUBLE = 2.0;

const bool RANKING = true;
const bool NO_RANKING = false;
const bool OPEN = true;
const bool CLOSED = false;

const bool CLEAN_SHEET = true;
const bool CONCEDED = false;
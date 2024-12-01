#pragma once

#include <string>
#include <vector>

class Match_team {
public:
    Match_team(std::string name, int GF, std::vector <std::string> squad) : name(name), GF(GF),
                                                                            squad(squad) {}
    Match_team() {}
    int get_gf() { return GF; }
    std::string get_name() { return name; }
    std::vector <std::string> get_squad() { return squad; }
    bool is_player_in_squad(std::string player_name);
    int find_player_post(std::string player_name);
    std::vector <std::string> get_mentioned_players(int post1, int post2);
    std::vector <std::string> get_mentioned_players(int post1, int post2, int post3);
private:
    std::string name;
    int GF;
    std::vector <std::string> squad;
};
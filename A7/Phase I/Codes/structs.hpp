#pragma once

#include <string>

#include "constants.hpp"

struct Status
{
    bool injured;
    bool suspended;
    float score;
    Status() : injured(false), suspended(false), score(INIT) {}
};

struct Player_score
{
    std::string name;
    float score;
};

struct Match_team 
{
    std::string name;
    int GF;
    Match_team(std::string name, int GF_) : name(name), GF(GF_) {}
    Match_team() {}
};
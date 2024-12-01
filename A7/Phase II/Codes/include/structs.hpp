#pragma once

#include <string>

#include "constants.hpp"

struct Status
{
    bool injured;
    bool suspended;
    Status() : injured(false), suspended(false) {}
};

struct Goal_info
{
    std::string scorer;
    std::string assistant;
};
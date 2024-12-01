#pragma once

#include "constants.hpp"

class Admin {
public:
    Admin() : username(ADMIN_USERNAME), password(ADMIN_PASSWORD) {}
    bool is_same_user_name(std::string _username) { return username == _username; }
    bool is_same_password(std::string _password) { return password == _password; }
private:
    const std::string username;
    const std::string password;
};
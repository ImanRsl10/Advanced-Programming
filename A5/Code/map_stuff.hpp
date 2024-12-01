#pragma once
#include "SFML/Graphics.hpp"

class Stuff {
public:
    Stuff(int x_pos, int y_pos, std::string file_name);
    sf::Sprite get_sprite();
    sf::Vector2f get_position();
    void set_position(int x, int y);
private:
    sf::Texture texture;
    sf::Sprite sprite;
    int x, y;
};
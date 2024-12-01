#pragma once

#include <SFML/Graphics.hpp>
#include "manual.hpp"

const std::string TURTEL_R = "attachments/turtel_r.png";
const std::string TURTEL_L = "attachments/turtel_l.png";

class Turtle {
public:
    Turtle(int x, int y);
    void move(Direction direction);
    void jump();
    void fall();
    sf::Vector2f get_position();
    sf::FloatRect get_pos();
    void draw(sf::RenderWindow& window);
private:
    // sf::RenderWindow* window;    
    sf::Texture texture;
    sf::Sprite sprite;
    int x_pos, y_pos; //needed?
    int velocity;
    bool faced_left;
    // sf::RenderWindow* window;
};
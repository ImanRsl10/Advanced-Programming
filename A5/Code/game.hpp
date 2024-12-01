#pragma once

#include <SFML/Graphics.hpp>
#include "turtle.hpp"
#include "map.hpp"

const std::string BACK_GROUND = "attachments/background_1.png";
const int JUMP_HIGHT = 100;

class Game {
public:
    Game();
    void start();
private:
    void draw();
    void handle_events();
    void tick();
private:
    sf::RenderWindow window;
    sf::Event event;
    sf::Sprite back_ground;
    sf::Vector2f jump_init_pos;
    sf::View camera;
    Turtle turtle;
    Map map;
    bool is_jumping, on_air, on_grass;
};
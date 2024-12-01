#pragma once

#include "SFML/Graphics.hpp"
#include "map_stuff.hpp"
// #include "manual.hpp"

const char GRASS = '.';
const char STAR = '*';
const char BABY = 'O';
const std::string GRASS_TEXTURE = "attachments/grass.png";
const std::string STAR_TEXTURE = "attachments/star.png";
const std::string BABY_TEXTURE = "attachments/baby_turtle.png";
const std::string MAP = "attachments/map.txt";

class Map {
public:
    Map();
    void load();
    bool is_on_grass(sf::FloatRect object_pos);
    void draw(sf::RenderWindow& window);
private:
    // sf::Sprite grass;
    // sf::Texture texture;
    std::vector <Stuff*> grasses;
    std::vector <Stuff*> stars;
    std::vector <Stuff*> babies;
    int x, y;
};
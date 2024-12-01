#include "map.hpp"
#include <iostream>
#include <vector>
#include <fstream>

using namespace sf;
using namespace std;

Map::Map()
{
    x = 0;
    y = 0;
    // texture.loadFromFile(GRASS_TEXTURE);
    // grass.setTexture(texture);
    // grass.setPosition(x, y);
}

void Map::load()
{
    ifstream map_file(MAP);
    string line;
    while(getline(map_file, line))
    {
        for(char element : line)
        {
            if(element == GRASS)
            {
                grasses.push_back(new Stuff(x, y, GRASS_TEXTURE));
            }
            if(element == STAR)
                stars.push_back(new Stuff(x, y, STAR_TEXTURE));
            if(element == BABY)
                babies.push_back(new Stuff(x, y, BABY_TEXTURE));
            x += 200;
        }
        x = 0;
        y += 100;
    }
    map_file.close();
}

void Map::draw(RenderWindow& window)
{
    for(Stuff* grass : grasses)
        window.draw(grass->get_sprite());
    for(Stuff* star : stars)
        window.draw(star->get_sprite());
    for(Stuff* baby : babies)
        window.draw(baby->get_sprite());
}

bool Map::is_on_grass(FloatRect object_pos)
{
    for(Stuff* grass : grasses)
    {
        if(grass->get_sprite().getGlobalBounds().intersects(object_pos))
        {
            return true;
        }
    }
    return false;
}
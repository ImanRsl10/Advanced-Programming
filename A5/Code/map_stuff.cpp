#include "map_stuff.hpp"

using namespace std;
using namespace sf;

Stuff::Stuff(int x_pos, int y_pos, string file_name)
{
    x = x_pos;
    y = y_pos;
    texture.loadFromFile(file_name);
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}

Sprite Stuff::get_sprite()
{
    return sprite;
}

void Stuff::set_position(int x, int y)
{
    this->x = x;
    this->y = y;
}

Vector2f Stuff::get_position()
{
    Vector2f position;
    position.x = x;
    position.y = y;
    return position;
}
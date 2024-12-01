#include "turtle.hpp"

using namespace std;
using namespace sf;

Turtle::Turtle(int x, int y)
{
    texture.loadFromFile(TURTEL_R);
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
    sprite.setPosition(x, y);
    x_pos = x; y_pos = y;
    // sprite.setOrigin(percentage(HALF, texture.getSize().x), percentage(HALF, texture.getSize().y));
    velocity = 10.0;
    faced_left = false;
}

void Turtle::move(Direction direction)
{
    if(direction == RIGHT)
    {
        // cout << "FacingR:" << faced_left << endl;
        if(faced_left)
        {
            texture.loadFromFile(TURTEL_R);
            sprite.setTexture(texture);
            faced_left = false;
        }
        sprite.move(velocity, 0);
    }
    else if(direction == LEFT)
    {
        // cout << "FacingL:" << faced_left << endl;
        if(!faced_left)
        {
            faced_left = true;
            texture.loadFromFile(TURTEL_L);
            sprite.setTexture(texture);
        }
        sprite.move(-velocity, 0);
    }
}

void Turtle::fall()
{
    sprite.move(0, velocity);
}

void Turtle::jump()
{
    sprite.move(0, -velocity);
}

Vector2f Turtle::get_position()
{
    return sprite.getPosition();
}

void Turtle::draw(RenderWindow& window)
{
    window.draw(sprite);
}

FloatRect Turtle::get_pos()
{
    return sprite.getGlobalBounds();
}
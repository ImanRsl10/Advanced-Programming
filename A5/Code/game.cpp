#include "manual.hpp"
#include "game.hpp"

using namespace sf;
using namespace std;

Game::Game() : window(VideoMode(1080, 720), "Dalam"),
      turtle(50, 0), map() 
{
    Texture texture;
    texture.loadFromFile(BACK_GROUND);
    texture.setSmooth(true);
    back_ground.setTexture(texture);
    is_jumping = false;
    on_air = false;
    on_grass = false;
    camera.setCenter(turtle.get_position());
}

void Game::start()
{
    Clock clk;
    map.load();
    /*map.draw(window);
    while (window.isOpen())
    {
        // window.clear();
        window.display();
    }*/
    while (window.isOpen())
    {
        while(window.pollEvent(event))
            handle_events();
        draw();
        window.display();
        if (clk.getElapsedTime() >= milliseconds(20)) 
        {
            tick();
            clk.restart();
        }
    }
}

void Game::handle_events()
{
    if(event.type == Event::Closed)
        window.close();
    if(event.type == Event::KeyPressed)
    {
        if(event.key.code == Keyboard::Left)
            turtle.move(LEFT);
        else if(event.key.code == Keyboard::Right)
            turtle.move(RIGHT);
        if(event.key.code == Keyboard::Up && !on_air)
        {
            jump_init_pos = turtle.get_position();
            is_jumping = true;
        }
    }
}

void Game::tick()
{
    if(is_jumping)
    {
        if(turtle.get_position().y > jump_init_pos.y - JUMP_HIGHT)
        {
            turtle.jump();
            on_air = true;
        }
        else
            is_jumping = false;
    }
    else
    {
        on_air = false;
        if(!map.is_on_grass(turtle.get_pos()))
            turtle.fall();
    }
}

void Game::draw()
{
    window.clear(Color::Cyan);
    camera.setCenter(turtle.get_position());
    window.setView(camera);
    // window.draw(back_ground);
    map.draw(window);
    turtle.draw(window);
}
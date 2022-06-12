#ifndef __AIRPLANE_GAME_HPP__
#define __AIRPLANE_GAME_HPP__

#include "../include/world.hpp"
#include "../include/player.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

class Game
{
public:
         Game();
    void Run();
    
private:
    void ProcessInput();
    void Update(sf::Time delta_time);
    void Render();

private:
    static const sf::Time time_per_frame_;
    sf::RenderWindow      window_;
    World                 world_;
    Player                player_;
};

#endif

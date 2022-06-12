#ifndef __AIRPLANE_GAME_STATE_HPP__
#define __AIRPLANE_GAME_STATE_HPP__

#include "../include/state.hpp"
#include "../include/world.hpp"
#include "../include/player.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class GameState : public State
{
public:
                 GameState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool Update(sf::Time dt);
    virtual bool HandleEvent(const sf::Event& event);


private:
    World   world_;
    Player& player_;
};

#endif // __AIRPLANE_GAME_STATE_HPP__

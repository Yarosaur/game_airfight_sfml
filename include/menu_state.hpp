#ifndef __AIRPLANE_MENU_STATE_HPP__
#define __AIRPLANE_MENU_STATE_HPP__

#include "../include/state.hpp"
#include "../include/container.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class MenuState : public State
{
public:
    MenuState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool Update(sf::Time dt);
    virtual bool HandleEvent(const sf::Event& event);


private:
    sf::Sprite background_sprite_;

    GUI::Container gui_container_;
};

#endif // __AIRPLANE_MENU_STATE_HPP__

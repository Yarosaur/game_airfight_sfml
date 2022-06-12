#ifndef __AIRPLANE_TITLE_STATE_HPP__
#define __AIRPLANE_TITLE_STATE_HPP__

#include "../include/state.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class TitleState : public State
{
public:
    TitleState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool Update(sf::Time dt);
    virtual bool HandleEvent(const sf::Event& event);


private:
    sf::Sprite background_sprite_;
    sf::Text text_;

    bool show_text_;
    sf::Time text_effect_time_;
};

#endif // __AIRPLANE_TITLE_STATE_HPP__

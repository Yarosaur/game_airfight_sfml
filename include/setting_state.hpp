#ifndef __AIRPLANE_SETTINGS_STATE_HPP__
#define __AIRPLANE_SETTINGS_STATE_HPP__

#include "../include/state.hpp"
#include "../include/player.hpp"
#include "../include/container.hpp"
#include "../include/button.hpp"
#include "../include/label.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>


class SettingsState : public State
{
public:
    SettingsState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool Update(sf::Time dt);
    virtual bool HandleEvent(const sf::Event& event);


private:
    void UpdateLabels();
    void AddButtonLabel(Player::Action action, float y,
			const std::string& text, Context context);


private:
    sf::Sprite background_sprite_;
    GUI::Container gui_container_;
    std::array<GUI::Button::Ptr, Player::ActionCount> binding_buttons_;
    std::array<GUI::Label::Ptr, Player::ActionCount> binding_labels_;
};

#endif // __AIRPLANE_SETTINGS_STATE_HPP__

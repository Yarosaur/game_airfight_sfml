#include "../include/pause_state.hpp"
#include "../include/button.hpp"
#include "../include/utility.hpp"
#include "../include/resource_holder.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


PauseState::PauseState(StateStack& stack, Context context)
    : State(stack, context)
    , background_sprite_()
    , paused_text_()
    , gui_container_()
{
    sf::Font& font {context.fonts_->Get(FontID::Main)};
    sf::Vector2f window_size {context.window_->getSize()};

    paused_text_.setFont(font);
    paused_text_.setString("Game Paused");	
    paused_text_.setCharacterSize(70);
    CenterOrigin(paused_text_);
    paused_text_.setPosition(0.5f * window_size.x, 0.4f * window_size.y);

    auto return_button {std::make_shared<GUI::Button>(*context.fonts_, *context.textures_)};
    return_button->setPosition(0.5f * window_size.x - 100, 0.4f * window_size.y + 75);
    return_button->SetText("Return");
    return_button->SetCallback([this] ()
				   {
				       RequestStackPop();
				   });

    auto back_to_menu_button {std::make_shared<GUI::Button>(*context.fonts_, *context.textures_)};
    back_to_menu_button->setPosition(0.5f * window_size.x - 100, 0.4f * window_size.y + 125);
    back_to_menu_button->SetText("Back to menu");
    back_to_menu_button->SetCallback([this] ()
					 {
					     RequestStateClear();
					     RequestStackPush(StateID::Menu);
					 });

    gui_container_.Pack(return_button);
    gui_container_.Pack(back_to_menu_button);
}


void PauseState::draw()
{
    sf::RenderWindow& window {*GetContext().window_};
    window.setView(window.getDefaultView());

    sf::RectangleShape background_shape;
    background_shape.setFillColor(sf::Color(0, 0, 0, 150));
    background_shape.setSize(window.getView().getSize());

    window.draw(background_shape);
    window.draw(paused_text_);
    window.draw(gui_container_);
}


bool PauseState::Update(sf::Time)
{
    return false;
}


bool PauseState::HandleEvent(const sf::Event& event)
{
    gui_container_.HandleEvent(event);
    return false;
}

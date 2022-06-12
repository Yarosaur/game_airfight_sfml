#include "../include/menu_state.hpp"
#include "../include/button.hpp"
#include "../include/utility.hpp"
#include "../include/resource_holder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


MenuState::MenuState(StateStack& stack, Context context)
    : State(stack, context)
    , gui_container_()
{
    sf::Texture& texture {context.textures_->Get(TextureID::TitleScreen)};
    background_sprite_.setTexture(texture);

    auto play_button {std::make_shared<GUI::Button>(*context.fonts_, *context.textures_)};
    play_button->setPosition(100, 250);
    play_button->SetText("Play");
    play_button->SetCallback([this] ()
				{
				    RequestStackPop();
				    RequestStackPush(StateID::Game);
				});

    auto settings_button {std::make_shared<GUI::Button>(*context.fonts_, *context.textures_)};
    settings_button->setPosition(100, 300);
    settings_button->SetText("Settings");
    settings_button->SetCallback([this] ()
				    {
					RequestStackPush(StateID::Settings);
				    });

    auto exit_button {std::make_shared<GUI::Button>(*context.fonts_, *context.textures_)};
    exit_button->setPosition(100, 350);
    exit_button->SetText("Exit");
    exit_button->SetCallback([this] ()
				{
				    RequestStackPop();
				});

    gui_container_.Pack(play_button);
    gui_container_.Pack(settings_button);
    gui_container_.Pack(exit_button);
}


void MenuState::draw()
{
    sf::RenderWindow& window {*GetContext().window_};

    window.setView(window.getDefaultView());
    window.draw(background_sprite_);
    window.draw(gui_container_);
}


bool MenuState::Update(sf::Time)
{
    return true;
}


bool MenuState::HandleEvent(const sf::Event& event)
{
   gui_container_.HandleEvent(event);
   return false;
}

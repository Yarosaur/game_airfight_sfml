#include "../include/title_state.hpp"
#include "../include/utility.hpp"
#include "../include/resource_holder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>


TitleState::TitleState(StateStack& stack, Context context)
    : State(stack, context)
    , text_()
    , show_text_(true)
    , text_effect_time_(sf::Time::Zero)
{
    background_sprite_.setTexture(context.textures_->Get(TextureID::TitleScreen));

    text_.setFont(context.fonts_->Get(FontID::Main));
    text_.setString("Press any key to start");
    CenterOrigin(text_);
    text_.setPosition(context.window_->getView().getSize() / 2.f);
}




void TitleState::draw()
{
    sf::RenderWindow& window {*GetContext().window_};
    window.draw(background_sprite_);

    if (show_text_)
    {
	window.draw(text_);
    }
}


bool TitleState::Update(sf::Time dt)
{
    text_effect_time_ += dt;

    if (text_effect_time_ >= sf::seconds(0.5f))
    {
	show_text_ = !show_text_;
	text_effect_time_ = sf::Time::Zero;
    }

    return true;
}


bool TitleState::HandleEvent(const sf::Event& event)
{
    // If any key is pressed, trigger the next screen
    if (event.type == sf::Event::KeyPressed)
    {
	RequestStackPop();
	RequestStackPush(StateID::Menu);
    }

    return true;
}

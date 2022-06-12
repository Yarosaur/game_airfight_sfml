#include "../include/loading_state.hpp"
#include "../include/utility.hpp"
#include "../include/resource_holder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


LoadingState::LoadingState(StateStack& stack, Context context)
    : State(stack, context)
{
    sf::RenderWindow& window {*GetContext().window_};
    sf::Font& font {context.fonts_->Get(FontID::Main)};
    sf::Vector2f view_size {window.getView().getSize()};

    loading_text_.setFont(font);
    loading_text_.setString("Loading Resources");
    CenterOrigin(loading_text_);
    loading_text_.setPosition(view_size.x / 2.f, view_size.y / 2.f + 50.f);

    progress_bar_background_.setFillColor(sf::Color::White);
    progress_bar_background_.setSize(sf::Vector2f(view_size.x - 20, 10));
    progress_bar_background_.setPosition(10, loading_text_.getPosition().y + 40);

    progress_bar_.setFillColor(sf::Color(100,100,100));
    progress_bar_.setSize(sf::Vector2f(200, 10));
    progress_bar_.setPosition(10, loading_text_.getPosition().y + 40);

    SetCompletion(0.f);

    loading_task_.Execute();
}


void LoadingState::draw()
{
    sf::RenderWindow& window {*GetContext().window_};

    window.setView(window.getDefaultView());

    window.draw(loading_text_);
    window.draw(progress_bar_background_);
    window.draw(progress_bar_);
}


bool LoadingState::Update(sf::Time)
{
    // Update the progress bar from the remote task or finish it
    if (loading_task_.IsFinished())
    {
	RequestStackPop();
	RequestStackPush(StateID::Game);
    }
    else
    {
	SetCompletion(loading_task_.GetCompletion());
    }
    return true;
}


bool LoadingState::HandleEvent(const sf::Event& event)
{
    return true;
}


void LoadingState::SetCompletion(float percent)
{
    if (percent > 1.f) // clamp
	percent = 1.f;

    progress_bar_.setSize(sf::Vector2f(progress_bar_background_.getSize().x * percent,
				       progress_bar_.getSize().y));
}

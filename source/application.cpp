#include "../include/application.hpp"
#include "../include/utility.hpp"
#include "../include/state.hpp"
#include "../include/state_stack.hpp"
#include "../include/title_state.hpp"
#include "../include/game_state.hpp"
#include "../include/menu_state.hpp"
#include "../include/pause_state.hpp"
#include "../include/settings_state.hpp"

#include <sstream>


const sf::Time Application::time_per_frame_ = sf::seconds(1.f/60.f);

Application::Application()
    : window_(sf::VideoMode(640, 480), "States", sf::Style::Close)
    , textures_()
    , fonts_()
    , player_()
    , state_stack_(State::Context(window_, textures_, fonts_, player_))
    , statistics_text_()
    , statistics_update_time_()
    , statistics_num_frames_(0)
{
    window_.setKeyRepeatEnabled(false);

    fonts_.Load(FontID::Main, "./media/Sansation.ttf");
    textures_.Load(TextureID::TitleScreen, "./media/textures/TitleScreen.png");
    textures_.Load(TextureID::ButtonNormal, "./media/textures/ButtonNormal.png");
    textures_.Load(TextureID::ButtonSelected, "./media/textures/ButtonSelected.png");
    textures_.Load(TextureID::ButtonPressed, "./media/textures/ButtonPressed.png");
    
    statistics_text_.setFont(fonts_.Get(FontID::Main));
    statistics_text_.setPosition(5.f, 5.f);
    statistics_text_.setCharacterSize(10u);

    RegisterStates();
    state_stack_.PushState(StateID::Title);
}




void Application::Run()
{
    sf::Clock clock;
    sf::Time time_since_last_update {sf::Time::Zero};

    while (window_.isOpen())
    {
	sf::Time dt {clock.restart()};
	time_since_last_update += dt;
	while (time_since_last_update > time_per_frame_)
	{
	    time_since_last_update -= time_per_frame_;

	    ProcessInput();
	    Update(time_per_frame_);

	    // Check inside this loop, because stack might be empty before update() call
	    if (state_stack_.IsEmpty())
	    {
		window_.close();
	    }
	}

	UpdateStatistics(dt);
	Render();
    }
}


void Application::ProcessInput()
{
    sf::Event event;
    while (window_.pollEvent(event))
    {
	state_stack_.HandleEvent(event);

	if (event.type == sf::Event::Closed)
	{
	    window_.close();
	}
    }
}


void Application::Update(sf::Time dt)
{
    state_stack_.Update(dt);
}


void Application::Render()
{
    window_.clear();

    state_stack_.draw();

    window_.setView(window_.getDefaultView());
    window_.draw(statistics_text_);

    window_.display();
}


void Application::UpdateStatistics(sf::Time dt)
{
    statistics_update_time_ += dt;
    statistics_num_frames_ += 1;
    if (statistics_update_time_ >= sf::seconds(1.0f))
    {
	statistics_text_.setString("FPS: " + std::to_string(statistics_num_frames_));

	statistics_update_time_ -= sf::seconds(1.0f);
	statistics_num_frames_ = 0;
    }
}


void Application::RegisterStates()
{
    state_stack_.RegisterState<TitleState>(StateID::Title);
    state_stack_.RegisterState<MenuState>(StateID::Menu);
    state_stack_.RegisterState<GameState>(StateID::Game);
    state_stack_.RegisterState<PauseState>(StateID::Pause);
    state_stack_.RegisterState<SettingsState>(StateID::Settings);
}

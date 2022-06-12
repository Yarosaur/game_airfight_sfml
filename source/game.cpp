#include "../include/game.hpp"

#include <iostream>

const sf::Time Game::time_per_frame_ = sf::seconds(1.f/60.f);

Game::Game()
    : window_(sf::VideoMode(640, 480), "SFML Application")
    , world_(window_)
    , player_()
{
    window_.setKeyRepeatEnabled(false);
}


void Game::Run()
{
    sf::Clock clock;
    sf::Time time_since_last_update {sf::Time::Zero};
    while (window_.isOpen())
    {
	sf::Time elapsed_time {clock.restart()};
	time_since_last_update += elapsed_time;
	while (time_since_last_update > time_per_frame_)
	{
	    time_since_last_update -= time_per_frame_;
	    ProcessInput();
	    Update(time_per_frame_);
	}
	Render();
    }
}


void Game::ProcessInput()
{
    CommandQueue& commands {world_.GetCommandQueue()};
    
    sf::Event event;
    while (window_.pollEvent(event))
    {
	player_.HandleEvent(event, commands);

	if (event.type == sf::Event::Closed)
	{
	    window_.close();
	}
    }
    player_.HandleRealtimeInput(commands);
}


void Game::Update(sf::Time delta_time)
{
    world_.Update(delta_time);
}


void Game::Render()
{
    window_.clear();
    world_.Draw();
    window_.setView(window_.getDefaultView());
    window_.display();
}



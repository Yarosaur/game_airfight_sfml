#include "../include/game_state.hpp"


GameState::GameState(StateStack& stack, Context context)
    : State(stack, context)
    , world_(*context.window_)
    , player_(*context.player_)
{
}




void GameState::draw()
{
    world_.Draw();
}


bool GameState::Update(sf::Time dt)
{
    world_.Update(dt);

    CommandQueue& commands {world_.GetCommandQueue()};
    player_.HandleRealtimeInput(commands);

    return true;
}


bool GameState::HandleEvent(const sf::Event& event)
{
    // Game input handling
    CommandQueue& commands {world_.GetCommandQueue()};
    player_.HandleEvent(event, commands);

    // Escape pressed, trigger the pause screen
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
	RequestStackPush(StateID::Pause);
    }

    return true;
}

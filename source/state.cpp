#include "../include/state.hpp"
#include "../include/state_stack.hpp"


State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player)
: window_(&window)
, textures_(&textures)
, fonts_(&fonts)
, player_(&player)
{
}

State::State(StateStack& stack, Context context)
: stack_(&stack)
, context_(context)
{
}

State::~State()
{
}




void State::RequestStackPush(StateID state_id)
{
	stack_->PushState(state_id);
}


void State::RequestStackPop()
{
	stack_->PopState();
}


void State::RequestStateClear()
{
	stack_->ClearStates();
}


State::Context State::GetContext() const
{
	return context_;
}

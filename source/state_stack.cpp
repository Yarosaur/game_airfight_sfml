#include "../include/state_stack.hpp"

#include <cassert>

StateStack::StateStack(State::Context context)
    : stack_()
    , pending_list_()
    , context_(context)
    , factories_()
{
}




void StateStack::Update(sf::Time dt)
{
    // Iterate from top to bottom, stop as soon as Update() returns false
    for (auto itr {stack_.rbegin()}; itr != stack_.rend(); ++itr)
    {
	if (!(*itr)->Update(dt))
	{
	    break;
	}
    }

    ApplyPendingChanges();
}


void StateStack::draw()
{
    // Draw all active states from bottom to top
    for (State::Ptr& state: stack_)
    {
	state->draw();
    }
}


void StateStack::HandleEvent(const sf::Event& event)
{
    // Iterate from top to bottom, stop as soon as HandleEvent() returns false
    for (auto itr {stack_.rbegin()}; itr != stack_.rend(); ++itr)
    {
	if (!(*itr)->HandleEvent(event))
	{
	    break;
	}
    }

    ApplyPendingChanges();
}


void StateStack::PushState(StateID state_id)
{
	pending_list_.push_back(PendingChange(Push, state_id));
}


void StateStack::PopState()
{
	pending_list_.push_back(PendingChange(Pop));
}


void StateStack::ClearStates()
{
	pending_list_.push_back(PendingChange(Clear));
}


bool StateStack::IsEmpty() const
{
	return stack_.empty();
}


State::Ptr StateStack::CreateState(StateID state_id)
{
    auto found {factories_.find(state_id)};
    assert(found != factories_.end());

    return found->second();
}


void StateStack::ApplyPendingChanges()
{
    for (PendingChange change: pending_list_)
    {
	switch (change.action_)
	{
	case Push:
	    stack_.push_back(CreateState(change.state_id_));
	    break;

	case Pop:
	    stack_.pop_back();
	    break;

	case Clear:
	    stack_.clear();
	    break;
	}
    }

    pending_list_.clear();
}


StateStack::PendingChange::PendingChange(Action action, StateID state_id)
    : action_(action)
    , state_id_(state_id)
{
}

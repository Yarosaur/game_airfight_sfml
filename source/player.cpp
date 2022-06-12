#include "../include/player.hpp"
#include "../include/command_queue.hpp"
#include "../include/aircraft.hpp"

#include <map>
#include <string>
#include <algorithm>


struct AircraftMover
{
    AircraftMover(float vx, float vy)
	: velocity(vx, vy)
	{
	}

    void operator() (Aircraft& aircraft, sf::Time) const
	{
	    aircraft.Accelerate(velocity);
	}

    sf::Vector2f velocity;
};

Player::Player()
{
    // Set initial key bindings
    key_binding_[sf::Keyboard::Left] = MoveLeft;
    key_binding_[sf::Keyboard::Right] = MoveRight;
    key_binding_[sf::Keyboard::Up] = MoveUp;
    key_binding_[sf::Keyboard::Down] = MoveDown;

    // Set initial action bindings
    InitializeActions();	

    // Assign all categories to player's aircraft
    for(auto& pair: action_binding_)
    {
	pair.second.category = Category::PlayerAircraft;
    }
}

void Player::HandleEvent(const sf::Event& event, CommandQueue& commands)
{
    if (event.type == sf::Event::KeyPressed)
    {
	// Check if pressed key appears in key binding, trigger command if so
	auto found {key_binding_.find(event.key.code)};
	if (found != key_binding_.end() && !IsRealtimeAction(found->second))
	{
	    commands.Push(action_binding_[found->second]);
	}
    }
}

void Player::HandleRealtimeInput(CommandQueue& commands)
{
    // Traverse all assigned keys and check if they are pressed
    for (auto pair: key_binding_)
    {
	// If key is pressed, lookup action and trigger corresponding command
	if (sf::Keyboard::isKeyPressed(pair.first) && IsRealtimeAction(pair.second))
	{
	    commands.Push(action_binding_[pair.second]);
	}
    }
}

void Player::AssignKey(Action action, sf::Keyboard::Key key)
{
    // Remove all keys that already map to action
    for (auto itr {key_binding_.begin()}; itr != key_binding_.end(); )
    {
	if (itr->second == action)
	    key_binding_.erase(itr++);
	else
	    ++itr;
    }

    // Insert new binding
    key_binding_[key] = action;
}

sf::Keyboard::Key Player::GetAssignedKey(Action action) const
{
    for (auto pair: key_binding_)
    {
	if (pair.second == action)
	{
	    return pair.first;
	}
    }

    return sf::Keyboard::Unknown;
}

void Player::InitializeActions()
{
    const float player_speed = 200.f;

    action_binding_[MoveLeft].action = DerivedAction<Aircraft>(AircraftMover(-player_speed, 0.f));
    action_binding_[MoveRight].action = DerivedAction<Aircraft>(AircraftMover(+player_speed, 0.f));
    action_binding_[MoveUp].action = DerivedAction<Aircraft>(AircraftMover(0.f, -player_speed));
    action_binding_[MoveDown].action = DerivedAction<Aircraft>(AircraftMover(0.f, +player_speed));
}

bool Player::IsRealtimeAction(Action action)
{
    switch (action)
    {
    case MoveLeft:
    case MoveRight:
    case MoveDown:
    case MoveUp:
	return true;

    default:
	return false;
    }
}

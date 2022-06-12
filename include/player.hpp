#ifndef __AIRPLANE_PLAYER_HPP__
#define __AIRPLANE_PLAYER_HPP__

#include "../include/command.hpp"
#include "../include/command_queue.hpp"

#include <map>

#include <SFML/Window/Event.hpp>


class Player
{
public:
    enum Action
    {
	MoveLeft,
	MoveRight,
	MoveUp,
	MoveDown,
	ActionCount
    };


public:
    Player();

    void HandleEvent(const sf::Event& event, CommandQueue& commands);
    void HandleRealtimeInput(CommandQueue& commands);

    void AssignKey(Action action, sf::Keyboard::Key key);
    sf::Keyboard::Key GetAssignedKey(Action action) const;


private:
    void InitializeActions();
    static bool	IsRealtimeAction(Action action);
    

private:
    std::map<sf::Keyboard::Key, Action>	key_binding_;
    std::map<Action, Command> action_binding_;
};

#endif // __AIRPLANE_PLAYER_HPP__

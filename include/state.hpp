#ifndef __AIRPLANE_STATE_HPP__
#define __AIRPLANE_STATE_HPP__

#include "../include/state_identifier.hpp"
#include "../include/resource_identifier.hpp"

#include <memory>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>


class StateStack;
class Player;

class State
{
public:
    typedef std::unique_ptr<State> Ptr;

    struct Context
    {
	Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player);

	sf::RenderWindow* window_;
	TextureHolder* textures_;
	FontHolder* fonts_;
	Player* player_;
    };


public:
    State(StateStack& stack, Context context);
    virtual ~State();

    virtual void draw() = 0;
    virtual bool Update(sf::Time dt) = 0;
    virtual bool HandleEvent(const sf::Event& event) = 0;


protected:
    void RequestStackPush(StateID state_id);
    void RequestStackPop();
    void RequestStateClear();

    Context GetContext() const;


private:
    StateStack*	stack_;
    Context context_;
};

#endif // __AIRPLANE_STATE_HPP__

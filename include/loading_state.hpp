#ifndef __AIRPLANE_LOADING_STATE_HPP__
#define __AIRPLANE_LOADING_STATE_HPP__

#include "../include/state.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../include/parallel_task.hpp"


class LoadingState : public State
{
public:
	LoadingState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool Update(sf::Time dt);
	virtual bool HandleEvent(const sf::Event& event);

	void SetCompletion(float percent);

private:
	sf::Text loading_text_;
	sf::RectangleShape progress_bar_background_;
	sf::RectangleShape progress_bar_;

	ParallelTask loading_task_;
};

#endif // __AIRPLANE_LOADING_STATE_HPP__

#ifndef __AIRPLANE_STATE_STACK_HPP__
#define __AIRPLANE_STATE_STACK_HPP__

#include "../include/state.hpp"

#include <vector>
#include <utility>
#include <functional>
#include <map>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>



class StateStack : private sf::NonCopyable
{
public:
    enum Action
    {
	Push,
	Pop,
	Clear,
    };


public:		
    explicit   StateStack(State::Context context);

    template <typename T>
    void       RegisterState(StateID state_id);

    void       Update(sf::Time dt);
    void       draw();
    void       HandleEvent(const sf::Event& event);

    void       PushState(StateID state_id);
    void       PopState();
    void       ClearStates();

    bool       IsEmpty() const;


private:
    State::Ptr CreateState(StateID state_id);
    void       ApplyPendingChanges();


private:
    struct PendingChange
    {
	explicit PendingChange(Action action, StateID state_id = StateID::None);

	Action action_;
	StateID state_id_;
    };


private:
    std::vector<State::Ptr>                        stack_;
    std::vector<PendingChange>                     pending_list_;
    State::Context                                 context_;
    std::map<StateID, std::function<State::Ptr()>> factories_;
};


template <typename T>
void StateStack::RegisterState(StateID state_id)
{
    factories_[state_id] = [this] ()
			      {
				  return State::Ptr(std::make_unique<T>(*this, context_));
			      };
}

#endif // __AIRPLANE_STATE_STACK_HPP__

#ifndef __AIRPLANE_APPLICATION_HPP__
#define __AIRPLANE_APPLICATION_HPP__

#include "../include/resource_holder.hpp"
#include "../include/resource_identifier.hpp"
#include "../include/player.hpp"
#include "../include/state_stack.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>


class Application
{
public:
         Application();
    void Run();
		

private:
    void ProcessInput();
    void Update(sf::Time dt);
    void Render();

    void UpdateStatistics(sf::Time dt);
    void RegisterStates();


private:
    static const sf::Time time_per_frame_;

    sf::RenderWindow      window_;
    TextureHolder         textures_;
    FontHolder            fonts_;
    Player                player_;
    StateStack            state_stack_;

    sf::Text              statistics_text_;
    sf::Time              statistics_update_time_;
    std::size_t           statistics_num_frames_;
};

#endif // __AIRPLANE_APPLICATION_HPP__

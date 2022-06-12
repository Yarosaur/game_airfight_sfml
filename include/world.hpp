#ifndef __AIRPLANE_WORLD_HPP__
#define __AIRPLANE_WORLD_HPP__

#include "../include/resource_holder.hpp"
#include "../include/resource_identifier.hpp"
#include "../include/scene_node.hpp"
#include "../include/sprite_node.hpp"
#include "../include/aircraft.hpp"
#include "../include/command_queue.hpp"
#include "../include/command.hpp"

#include <array>
#include <queue>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics.hpp>


class World : private sf::NonCopyable
{
public:
    explicit World(sf::RenderWindow& window);
    
    void Update(sf::Time dt);
    void Draw();

    CommandQueue& GetCommandQueue();

private:
    void LoadTextures();
    void BuildScene();
    void AdaptPlayerPosition();
    void AdaptPlayerVelocity();


private:
    enum class Layer
    {
	Background,
	Air,
	LayerCount
    };


private:
    sf::RenderWindow& window_;
    sf::View world_view_;
    TextureHolder textures_;

    SceneNode scene_graph_;
    std::array<SceneNode*, static_cast<int>(Layer::LayerCount)> scene_layers_;
    CommandQueue command_queue_;

    sf::FloatRect world_bounds_;
    sf::Vector2f spawn_position_;
    float scroll_speed_;
    Aircraft* player_aircraft_;
};

#endif

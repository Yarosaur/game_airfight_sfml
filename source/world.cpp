#include "../include/world.hpp"

#include <cmath>

#include <SFML/Graphics/RenderWindow.hpp>


World::World(sf::RenderWindow& window)
    : window_         (window)
    , world_view_     (window.getDefaultView())
    , textures_       () 
    , scene_graph_    ()
    , scene_layers_   ()
    , world_bounds_   (0.f, 0.f, world_view_.getSize().x, 2000.f)
    , spawn_position_ (world_view_.getSize().x / 2.f,
		       world_bounds_.height - world_view_.getSize().y / 2.f)
    , scroll_speed_   (-50.f)
    , player_aircraft_(nullptr)
{
    LoadTextures();
    BuildScene();

    // Prepare the view
    world_view_.setCenter(spawn_position_);
}


void World::Update(sf::Time dt)
{
    // Scroll the world
    world_view_.move(0.f, scroll_speed_ * dt.asSeconds());	
    player_aircraft_->SetVelocity(0.f, 0.f);
    
    // Forward commands to scene graph, adapt velocity (scrolling, diagonal correction)
    while (!command_queue_.IsEmpty())
    {
	scene_graph_.OnCommand(command_queue_.Pop(), dt);
    }
    AdaptPlayerVelocity();

    // Regular update step, adapt position (correct if outside view)
    scene_graph_.Update(dt);
    AdaptPlayerPosition();
}


void World::Draw()
{
    window_.setView(world_view_);
    window_.draw(scene_graph_);
}


CommandQueue& World::GetCommandQueue()
{
    return command_queue_;
}


void World::LoadTextures()
{
    textures_.Load(TextureID::Eagle,  "./media/textures/Eagle.png");
    textures_.Load(TextureID::Raptor, "./media/textures/Raptor.png");
    textures_.Load(TextureID::Desert, "./media/textures/Desert.png");
}


void World::BuildScene()
{
    // Initialize the different layers
    for (std::size_t i {0}; i < static_cast<std::size_t>(Layer::LayerCount); ++i)
    {
	SceneNode::PtrNode layer(std::make_unique<SceneNode>());
	scene_layers_[i] = layer.get();

	scene_graph_.AttachChild(std::move(layer));
    }

    // Prepare the tiled background
    sf::Texture& texture      {textures_.Get(TextureID::Desert)};
    sf::IntRect  texture_rect (world_bounds_);
    texture.setRepeated(true);

    // Add the background sprite to the scene
    auto background_sprite { std::make_unique<SpriteNode>(texture, texture_rect) };
    background_sprite->setPosition(world_bounds_.left, world_bounds_.top);
    scene_layers_[static_cast<std::size_t>(Layer::Background)]->AttachChild(std::move(background_sprite));

    // Add player's aircraft
    auto leader { std::make_unique<Aircraft>(Aircraft::Type::Eagle, textures_) };
    player_aircraft_ = leader.get();
    player_aircraft_->setPosition(spawn_position_);
    player_aircraft_->SetVelocity(40.f, scroll_speed_);
    scene_layers_[static_cast<std::size_t>(Layer::Air)]->AttachChild(std::move(leader));
}


void World::AdaptPlayerPosition()
{
    // Keep player's position inside the screen bounds, at least border_distance units from the border
    sf::FloatRect view_bounds     (world_view_.getCenter() - world_view_.getSize() / 2.f,
				   world_view_.getSize());
    const float   border_distance {40.f};
    sf::Vector2f  position        {player_aircraft_->getPosition()};

    position.x = std::max(position.x, view_bounds.left + border_distance);
    position.x = std::min(position.x, view_bounds.left + view_bounds.width - border_distance);
    position.y = std::max(position.y, view_bounds.top + border_distance);
    position.y = std::min(position.y, view_bounds.top + view_bounds.height - border_distance);
    player_aircraft_->setPosition(position);
}

void World::AdaptPlayerVelocity()
{
    sf::Vector2f velocity {player_aircraft_->GetVelocity()};

    // If moving diagonally, reduce velocity (to have always same velocity)
    if (velocity.x != 0.f && velocity.y != 0.f)
    {
	player_aircraft_->SetVelocity(velocity / std::sqrt(2.f));
    }

    // Add scrolling velocity
    player_aircraft_->Accelerate(0.f, scroll_speed_);
}

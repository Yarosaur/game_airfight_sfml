#include "../include/aircraft.hpp"

TextureID ToTextureID(Aircraft::Type type)
{
    switch (type)
    {
    case Aircraft::Type::Eagle:
	return TextureID::Eagle;

    case Aircraft::Type::Raptor:
	return TextureID::Raptor;
    }
    return TextureID::Eagle;
}


Aircraft::Aircraft(Type type, const TextureHolder& textures)
    :type_(type)
    ,sprite_(textures.Get(ToTextureID(type)))
{
    sf::FloatRect bounds {sprite_.getLocalBounds()};
    sprite_.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}


void Aircraft::DrawCurrent(sf::RenderTarget& target,
			   sf::RenderStates states) const
{
    target.draw(sprite_, states);
}


unsigned int Aircraft::GetCategory() const
{
    switch (type_)
    {
    case Type::Eagle:
	return Category::PlayerAircraft;

    default:
	return Category::EnemyAircraft;
    }
}




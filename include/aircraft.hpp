#ifndef __AIRPLANE_AIRCRAFT_HPP__
#define __AIRPLANE_AIRCRAFT_HPP__


#include "../include/entity.hpp"
#include "../include/resource_holder.hpp"
#include "../include/resource_identifier.hpp"

#include <SFML/Graphics.hpp>

class Aircraft: public Entity
{
public:
    enum class Type
    {
	Eagle,
	Raptor
    };

    explicit     Aircraft(Type type, const TextureHolder& textures);
    
    virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual uint GetCategory() const;

private:
    Type         type_;
    sf::Sprite   sprite_;
};

#endif //__AIRPLANE_AIRCRAFT_HPP__

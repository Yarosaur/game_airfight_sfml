#include "../include/utility.hpp"

#include <cmath>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


void CenterOrigin(sf::Sprite& sprite)
{
    sf::FloatRect bounds {sprite.getLocalBounds()};
    sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
		     std::floor(bounds.top + bounds.height / 2.f));
}


void CenterOrigin(sf::Text& text)
{
    sf::FloatRect bounds {text.getLocalBounds()};
    text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
		   std::floor(bounds.top + bounds.height / 2.f));
}

#ifndef __AIRPLANE_RESOURCE_IDENTIFIER_HPP__
#define __AIRPLANE_RESOURCE_IDENTIFIER_HPP__

#include "../include/resource_holder.hpp"

#include <SFML/Graphics.hpp>


enum class TextureID
{
    Eagle,
    Raptor,
    Desert,
    TitleScreen,
    ButtonNormal,
    ButtonSelected,
    ButtonPressed
};

enum class FontID
{
    Main,
};


typedef ResourceHolder<sf::Texture, TextureID> TextureHolder;
typedef ResourceHolder<sf::Font, FontID> FontHolder;

#endif // __RESOURCE_IDENTIFIER__

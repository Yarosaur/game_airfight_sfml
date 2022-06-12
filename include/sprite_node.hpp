#ifndef __AIRPLANE_SPRITE_NODE_HPP__
#define __AIRPLANE_SPRITE_NODE_HPP__

#include "../include/scene_node.hpp"

#include <SFML/Graphics/Sprite.hpp>


class SpriteNode : public SceneNode
{
public:
    explicit SpriteNode(const sf::Texture& texture);
    SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);


private:
    virtual void DrawCurrent(sf::RenderTarget& target,
			     sf::RenderStates states) const;


private:
    sf::Sprite sprite_;
};

#endif // __AIRPLANE_SPRITE_NODE_HPP__

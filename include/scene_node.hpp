#ifndef __AIRPLANE_SCENE_NODE_HPP__
#define __AIRPLANE_SCENE_NODE_HPP__

#include "../include/category.hpp"
#include "../include/command.hpp"

#include <memory>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class SceneNode: public sf::Transformable, public sf::Drawable,
		 private sf::NonCopyable
{
public:
    typedef std::unique_ptr <SceneNode> PtrNode;

public:
    SceneNode();

    void AttachChild(PtrNode child);
    PtrNode DetachChild(const SceneNode& node);

    void Update(sf::Time dt);

    sf::Transform GetWorldTransform() const;
    sf::Vector2f GetWorldPosition() const;

    void OnCommand(const Command& command, sf::Time dt);
    virtual unsigned int GetCategory() const;
    

private:
    //draw function inherited from sf::Drawable, where it's pure virtual
    virtual void draw(sf::RenderTarget& target,
		      sf::RenderStates states) const;

    virtual void DrawCurrent(sf::RenderTarget& target,
			     sf::RenderStates states) const;

    void DrawChildren(sf::RenderTarget& target,
			     sf::RenderStates states) const;

    virtual void UpdateCurrent(sf::Time dt);
    void UpdateChildren(sf::Time dt);

private:
    std::vector <PtrNode> children_;
    SceneNode* parent_;
};

#endif // __SCENE_NODE__

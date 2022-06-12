#include "../include/scene_node.hpp"

#include <utility>
#include <algorithm>
#include <cassert>


SceneNode::SceneNode()
: children_()
, parent_(nullptr)
{
}


void SceneNode::AttachChild(PtrNode child)
{
    child -> parent_ = this;
    children_.push_back(std::move(child));
}


SceneNode::PtrNode SceneNode::DetachChild(const SceneNode& node)
{
    auto found {std::find_if(children_.begin(), children_.end(),
			     [&] (PtrNode& p) -> bool { return p.get() == &node; })};
    
    assert(found != children_.end());

    PtrNode result {std::move(*found)};
    result->parent_ = nullptr;
    children_.erase(found);
    return result;
}


void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Apply transform of current node
    states.transform *= getTransform();

    // Draw node and children with changed transform
    DrawCurrent(target, states);
    DrawChildren(target, states);
}


void SceneNode::DrawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
    // Do nothing by default
}


void SceneNode::DrawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const PtrNode& child: children_)
    {
	child->draw(target, states);
    }
}


void SceneNode::Update(sf::Time dt)
{
    UpdateCurrent(dt);
    UpdateChildren(dt);
}


void SceneNode::UpdateCurrent(sf::Time)
{
    // Do nothing by default
}


void SceneNode::UpdateChildren(sf::Time dt)
{
    for (PtrNode& child: children_)
    {
	child->Update(dt);
    }
}


sf::Transform SceneNode::GetWorldTransform() const
{
    sf::Transform transform {sf::Transform::Identity};

    for (const SceneNode* node {this}; node != nullptr; node = node->parent_)
	transform = node->getTransform() * transform;

    return transform;
}


sf::Vector2f SceneNode::GetWorldPosition() const
{
    return GetWorldTransform() * sf::Vector2f();
}


void SceneNode::OnCommand(const Command& command, sf::Time dt)
{
    // Command current node, if category matches
    if (command.category & GetCategory())
    {
	command.action(*this, dt);
    }

    // Command children
    for (PtrNode& child: children_)
    {
	child->OnCommand(command, dt);
    }
}

unsigned int SceneNode::GetCategory() const
{
    return Category::Scene;
}

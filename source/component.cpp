#include "../include/component.hpp"

namespace GUI
{

    Component::Component()
	: selected_(false)
	, active_(false)
    {
    }

    
    Component::~Component()
    {
    }



    
    bool Component::IsSelected() const
    {
	return selected_;
    }

    
    void Component::Select()
    {
	selected_ = true;
    }

    
    void Component::Deselect()
    {
	selected_ = false;
    }

    
    bool Component::IsActive() const
    {
	return active_;
    }

    
    void Component::Activate()
    {
	active_ = true;
    }

    
    void Component::Deactivate()
    {
	active_ = false;
    }

}

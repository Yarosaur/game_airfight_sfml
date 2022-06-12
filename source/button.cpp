#include "../include/button.hpp"
#include "../include/utility.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{

    Button::Button(const FontHolder& fonts, const TextureHolder& textures)
	: callback_()
	, normal_texture_(textures.Get(TextureID::ButtonNormal))
	, selected_texture_(textures.Get(TextureID::ButtonSelected))
	, pressed_texture_(textures.Get(TextureID::ButtonPressed))
	, sprite_()
	, text_("", fonts.Get(FontID::Main), 16)
	, toggle_(false)
    {
	sprite_.setTexture(normal_texture_);

	sf::FloatRect bounds {sprite_.getLocalBounds()};
	text_.setPosition(bounds.width / 2.f, bounds.height / 2.f);
    }



    
    void Button::SetCallback(Callback callback)
    {
	callback_ = std::move(callback);
    }

    
    void Button::SetText(const std::string& text)
    {
	text_.setString(text);
	CenterOrigin(text_);
    }

    
    void Button::SetToggle(bool flag)
    {
	toggle_ = flag;
    }

    
    bool Button::IsSelectable() const
    {
	return true;
    }

    
    void Button::Select()
    {
	Component::Select();

	sprite_.setTexture(selected_texture_);
    }

    
    void Button::Deselect()
    {
	Component::Deselect();

	sprite_.setTexture(normal_texture_);
    }

    
    void Button::Activate()
    {
	Component::Activate();

	// If we are toggle then we should show that the button is pressed and thus "toggled".
	if (toggle_)
	    sprite_.setTexture(pressed_texture_);

	if (callback_)
	    callback_();

	// If we are not a toggle then deactivate the button since we are just momentarily activated.
	if (!toggle_)
	    Deactivate();
    }
    

    void Button::Deactivate()
    {
	Component::Deactivate();

	if (toggle_)
	{
	    // Reset texture to right one depending on if we are selected or not.
	    if (IsSelected())
		sprite_.setTexture(selected_texture_);
	    else
		sprite_.setTexture(normal_texture_);
	}
    }

    
    void Button::HandleEvent(const sf::Event&)
    {
    }

    
    void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
	states.transform *= getTransform();
	target.draw(sprite_, states);
	target.draw(text_, states);
    }

}

#ifndef __AIRPLANE_BUTTON_HPP__
#define __AIRPLANE_BUTTON_HPP__

#include "../include/component.hpp"
#include "../include/resource_identifier.hpp"
#include "../include/resource_holder.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>
#include <string>
#include <memory>
#include <functional>


namespace GUI
{

    class Button : public Component
    {
    public:
        typedef std::shared_ptr<Button> Ptr;
        typedef std::function<void()> Callback;


    public:
	Button(const FontHolder& fonts, const TextureHolder& textures);

        void SetCallback(Callback callback);
        void SetText(const std::string& text);
        void SetToggle(bool flag);

        virtual bool IsSelectable() const;
        virtual void Select();
        virtual void Deselect();

        virtual void Activate();
        virtual void Deactivate();

        virtual void HandleEvent(const sf::Event& event);


    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
        Callback callback_;
        const sf::Texture& normal_texture_;
        const sf::Texture& selected_texture_;
        const sf::Texture& pressed_texture_;
        sf::Sprite sprite_;
        sf::Text text_;
        bool toggle_;
    };

}

#endif // __AIRPLANE_BUTTON_HPP__

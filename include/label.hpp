#ifndef __AIRPLANE_LABEL_HPP__
#define __AIRPLANE_LABEL_HPP__

#include "../include/component.hpp"
#include "../include/resource_identifier.hpp"
#include "../include/resource_holder.hpp"

#include <SFML/Graphics/Text.hpp>


namespace GUI
{

    class Label : public Component
    {
    public:
        typedef std::shared_ptr<Label> Ptr;
            

    public:
	Label(const std::string& text, const FontHolder& fonts);

        virtual bool IsSelectable() const;
	void SetText(const std::string& text);

        virtual void HandleEvent(const sf::Event& event);


    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
        sf::Text text_;
    };

}

#endif // __AIRPLANE_LABEL_HPP__

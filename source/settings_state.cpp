#include "../include/settings_state.hpp"
#include "../include/utility.hpp"
#include "../include/resource_holder.hpp"

#include <string>

#include <SFML/Graphics/RenderWindow.hpp>


SettingsState::SettingsState(StateStack& stack, Context context)
    : State(stack, context)
    , gui_container_()
{
    background_sprite_.setTexture(context.textures_->Get(TextureID::TitleScreen));
	
    // Build key binding buttons and labels
    AddButtonLabel(Player::MoveLeft,  150.f, "Move Left", context);
    AddButtonLabel(Player::MoveRight, 200.f, "Move Right", context);
    AddButtonLabel(Player::MoveUp,    250.f, "Move Up", context);
    AddButtonLabel(Player::MoveDown,  300.f, "Move Down", context);

    UpdateLabels();

    auto back_button {std::make_shared<GUI::Button>(*context.fonts_, *context.textures_)};
    back_button->setPosition(80.f, 375.f);
    back_button->SetText("Back");
    back_button->SetCallback(std::bind(&SettingsState::RequestStackPop, this));

    gui_container_.Pack(back_button);
}




void SettingsState::draw()
{
    sf::RenderWindow& window {*GetContext().window_};

    window.draw(background_sprite_);
    window.draw(gui_container_);
}


bool SettingsState::Update(sf::Time)
{
    return true;
}


bool SettingsState::HandleEvent(const sf::Event& event)
{
    bool is_key_binding {false};
	
    // Iterate through all key binding buttons to see if they are being pressed, waiting for the user to enter a key
    for (std::size_t action {0}; action < Player::ActionCount; ++action)
    {
	if (binding_buttons_[action]->IsActive())
	{
	    is_key_binding = true;
	    if (event.type == sf::Event::KeyReleased)
	    {
		GetContext().player_->AssignKey(static_cast<Player::Action>(action), event.key.code);
		binding_buttons_[action]->Deactivate();
	    }
	    break;
	}
    }

    // If pressed button changed key bindings, update labels; otherwise consider other buttons in container
    if (is_key_binding)
	UpdateLabels();
    else
	gui_container_.HandleEvent(event);

    return false;
}


void SettingsState::UpdateLabels()
{
    Player& player {*GetContext().player_};

    for (std::size_t i {0}; i < Player::ActionCount; ++i)
    {
	sf::Keyboard::Key key {player.GetAssignedKey(static_cast<Player::Action>(i))};
	binding_labels_[i]->SetText(std::to_string(key));
    }
}

void SettingsState::AddButtonLabel(Player::Action action, float y, const std::string& text, Context context)
{
    binding_buttons_[action] = std::make_shared<GUI::Button>(*context.fonts_, *context.textures_);
    binding_buttons_[action]->setPosition(80.f, y);
    binding_buttons_[action]->SetText(text);
    binding_buttons_[action]->SetToggle(true);

    binding_labels_[action] = std::make_shared<GUI::Label>("", *context.fonts_);
    binding_labels_[action]->setPosition(300.f, y + 15.f);

    gui_container_.Pack(binding_buttons_[action]);
    gui_container_.Pack(binding_labels_[action]);
}

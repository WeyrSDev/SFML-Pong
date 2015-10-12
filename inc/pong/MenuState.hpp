#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "State.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>

class MenuState : public State
{
public:
  explicit MenuState( StateStack& stack );
  virtual bool handleInput( const sf::Event& event ) override;
  virtual bool update( sf::Time dt ) override;
  virtual void render() override;

private:
  enum class MenuOptions
  {
    PLAY,
    SETTINGS,
    CREDITS,
    EXIT,
  };

  void updateMenuText();

  sf::Sprite mBackgroundSprite;
  sf::Text mTitle;
  std::vector<sf::Text> mMenuOptions;
  std::size_t mMenuIndex;
};

#endif
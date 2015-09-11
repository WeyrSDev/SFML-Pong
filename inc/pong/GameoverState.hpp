#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include "State.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>

class GameoverState : public State
{
public:
  explicit GameoverState( StateStack& stack );
  bool handleInput( const sf::Event& event ) override;
  bool update( sf::Time dt ) override;
  void render() override;

private:
  enum class MenuOptions
  {
    PLAY,
    MENU,
    EXIT,
  };

  void updateMenuText();

  sf::Sprite mBackgroundSprite;
  sf::Text mGameoverText;
  std::vector<sf::Text> mMenuOptions;
  std::size_t mMenuIndex;
};

#endif
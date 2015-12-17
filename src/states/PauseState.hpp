#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include <engine/State.hpp>
#include <engine/TextMenu.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class PauseState : public State
{
public:
               PauseState( StateStack& stack, States id );

  virtual bool handleInput( const sf::Event& event ) override;
  virtual bool update( sf::Time dt ) override;
  virtual void render() override;
private:
  enum class MenuOption : unsigned int
  {
    RESUME = 0u,
    EXIT_MENU,
    EXIT,
  };

  sf::RectangleShape mBackgroundShape;
  sf::Text mPauseText;
  TextMenu mMenu;
};


#endif
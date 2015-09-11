#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include "State.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class PauseState : public State
{
public:
  explicit PauseState( StateStack& stack );

  virtual bool handleInput( const sf::Event& event ) override;
  virtual bool update( sf::Time dt ) override;
  virtual void render() override;
private:
  enum class MenuOptions
  {
    RESUME,
    EXIT,
  };

  void updateMenuText();

  sf::RectangleShape mBackgroundShape;
  sf::Text mPauseText;
  std::vector<sf::Text> mMenuOptions;
  std::size_t mMenuIndex;
};


#endif
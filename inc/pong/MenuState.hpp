#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "State.hpp"
#include <SFML/Graphics/Text.hpp>
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
    EXIT,
  };

  void updateMenuText();

  std::vector<sf::Text> mOptions;
  std::size_t mOptionsIndex;
};

#endif
#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include <engine/State.hpp>
#include <engine/TextMenu.hpp>
#include <vector>
#include <memory>

class MenuState : public core::State
{
public:
               MenuState( core::StateStack& stack, States id );
  virtual bool handleInput( const sf::Event& event ) override;
  virtual bool update( sf::Time dt ) override;
  virtual void render() override;

private:
  enum class MenuOption : unsigned int
  {
    PLAY    = 0u,
    OPTIONS = 1u,
    CREDITS = 2u,
    EXIT    = 3u,
  };

  core::TextMenu   mMenu;
  std::vector<std::unique_ptr<sf::Drawable>> mDrawObjects;
};

#endif
#ifndef CONTEXT_HPP
#define CONTEXT_HPP

namespace sf
{
  class RenderWindow;
}

struct Context
{
  Context(sf::RenderWindow& window)
    : window( &window )
  {}

  sf::RenderWindow* window;
};

#endif
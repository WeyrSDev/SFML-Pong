#ifndef BLACKBOARD_HPP
#define BLACKBOARD_HPP

#include <SFML/Window/Event.hpp>

struct Blackboard
{
  Blackboard()
    : gameOver( false )
    , playerWon( false )
    , keyEventType( sf::Event::KeyReleased )
  {}

  bool gameOver;
  bool playerWon;
  sf::Event::EventType keyEventType;
};

#endif
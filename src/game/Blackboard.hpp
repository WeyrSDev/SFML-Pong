#ifndef BLACKBOARD_HPP
#define BLACKBOARD_HPP

#include <SFML/Window/Event.hpp>

struct Blackboard
{
  bool gameOver;
  bool playerWon;
  sf::Event::EventType keyEventType;

  Blackboard()
    : gameOver( false )
    , playerWon( false )
    , keyEventType( sf::Event::KeyReleased )
  {}
};

#endif
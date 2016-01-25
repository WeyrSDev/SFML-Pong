#ifndef BLACKBOARD_HPP
#define BLACKBOARD_HPP

#include <SFML/Window/Event.hpp>

// central game data strucure
// holds all central variables which needed to be shared across
// all gamestates, like game-over state (win/loss) etc
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
#ifndef BLACKBOARD_HPP
#define BLACKBOARD_HPP

struct Blackboard
{
  Blackboard()
    : gameOver( false )
    , playerWon( false )
  {}

  bool gameOver;
  bool playerWon;  
};

#endif
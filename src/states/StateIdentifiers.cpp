#include "StateIdentifiers.hpp"

StateStrings initStateStrings()
{
  StateStrings data;
  data.emplace( States::NONE, std::string( "NONE" ) );
  data.emplace( States::TITLE, std::string( "TITLE" ) );
  data.emplace( States::MENU, std::string( "MENU" ) );
  data.emplace( States::GAME, std::string( "GAME" ) );
  data.emplace( States::PAUSE, std::string( "PAUSE" ) );
  data.emplace( States::GAMEOVER, std::string( "GAME_OVER" ) );
  data.emplace( States::OPTIONS, std::string( "OPTIONS" ) );
  data.emplace( States::CREDITS, std::string( "CREDITS" ) );

  return data;
}
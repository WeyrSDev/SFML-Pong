#ifndef STATE_IDENTIFIERS_HPP
#define STATE_IDENTIFIERS_HPP
#include <engine/Utility.hpp>
#include <map>

enum class States : unsigned short
{
  NONE = 0u,
  TITLE,
  MENU,
  GAME,
  PAUSE,
  GAMEOVER,
  OPTIONS,
  CREDITS,
  STATE_COUNT, // always needs to be last element
};

typedef std::map<States, std::string> StateStrings;
StateStrings initStateStrings();

#endif
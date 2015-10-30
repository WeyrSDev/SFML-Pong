#ifndef STATE_IDENTIFIERS_HPP
#define STATE_IDENTIFIERS_HPP

enum class States : unsigned int
{
  NONE = 0,
  TITLE,
  MENU,
  GAME,
  PAUSE,
  GAMEOVER,
  OPTIONS,
  CREDITS,
};

#endif
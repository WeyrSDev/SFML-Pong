#include "DataTables.hpp"

TitleStateStringData initTitleStrings()
{
  TitleStateStringData data;

  data.title = std::string{ "P O N G" };
  data.start = std::string{ "< press any key to start >" };
  data.creator = std::string{ "created by Sebastian 'SeriousITGuy' Brack" };

  return data;
}

MenuStateStringData initMenuStrings()
{
  MenuStateStringData data;

  data.play = std::string{ "PLAY" };
  data.options = std::string{ "OPTIONS" };
  data.credits = std::string{ "CREDITS" };
  data.exit = std::string{ "EXIT" };
  data.title = std::string{ "P O N G" };
  data.creator = std::string{ "created by Sebastian 'SeriousITGuy' Brack" };

  return data;
}

PauseStateStringData initPauseStrings()
{
  PauseStateStringData data;

  data.pause = std::string{ "GAME PAUSED" };
  data.resume = std::string{ "RESUME GAME" };
  data.restart = std::string{ "RESTART GAME" };
  data.menu = std::string{ "EXIT TO MENU" };
  data.exit = std::string{ "EXIT" };

  return data;
}

GameoverStateStringData initGameoverStrings()
{
  GameoverStateStringData data;

  data.line1Won = std::string{ "You have won!" };
  data.line2Won = std::string{ "Congratulations!" };
  data.line1Lost = std::string{ "You have lost!" };
  data.line2Lost = std::string{ "Sorry! Try again." };
  data.play = std::string{ "PLAY AGAIN" };
  data.menu = std::string{ "EXIT TO MENU" };
  data.exit = std::string{ "EXIT" };

  return data;
}

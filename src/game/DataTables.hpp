#ifndef DATATABLES_HPP
#define DATATABLES_HPP

#include <string>

struct TitleStateStringData
{
  std::string title;
  std::string start;
  std::string creator;
};

struct MenuStateStringData
{
  std::string play;
  std::string options;
  std::string credits;
  std::string exit;
  std::string title;
  std::string creator;
};

struct PauseStateStringData
{
  std::string pause;
  std::string resume;
  std::string restart;
  std::string menu;
  std::string exit;  
};

struct GameoverStateStringData
{
  std::string line1Won;
  std::string line2Won;
  std::string line1Lost;
  std::string line2Lost;
  std::string play;
  std::string menu;
  std::string exit;
};

TitleStateStringData initTitleStrings();
MenuStateStringData initMenuStrings();
PauseStateStringData initPauseStrings();
GameoverStateStringData initGameoverStrings();

#endif
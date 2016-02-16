#ifndef RESOURCE_IDENTIFIERS_HPP
#define RESOURCE_IDENTIFIERS_HPP

// add your texture identifiers here
// do not change the name or underlying type
// always mark the first entry as '=0u'
enum class Textures : unsigned short
{
  TITLE_BG = 0u,
  TILES,
};

// add your font identifiers here
// do not change the name or underlying type
// always mark the first entry as '=0u'
enum class Fonts : unsigned short
{
  MONOSPACE = 0u,
  SDS_8BIT,
  C64_Pixel,
  DP_COMIC,
  X7X5_PIXEL,
};

// add your music identifiers here
// do not change the name or underlying type
// always mark the first entry as '=0u'
enum class Music : unsigned short
{
  MENU_THEME = 0u,
  GAME_THEME,
};

// add your music identifiers here
// do not change the name or underlying type
// always mark the first entry as '=0u'
enum class Sounds : unsigned short
{

};

#endif
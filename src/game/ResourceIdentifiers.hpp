#ifndef RESOURCE_IDENTIFIERS_HPP
#define RESOURCE_IDENTIFIERS_HPP

namespace sf
{
  class Texture;
  class Font;
}

enum class Textures : unsigned short
{
  TITLE_BG = 0u,
};

enum class Fonts : unsigned short
{
  MONOSPACE = 0u,
  SDS_8BIT,
  C64_Pixel,
  DP_COMIC,
};

enum class Music : unsigned short
{
  MENU_THEME = 0u,
  GAME_THEME,
};

template <typename Resource, typename Identifier>
class ResourceCache;

typedef ResourceCache<sf::Texture, Textures> TextureCache;
typedef ResourceCache<sf::Font, Fonts> FontCache;

#endif
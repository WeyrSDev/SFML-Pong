#ifndef RESOURCE_IDENTIFIERS_HPP
#define RESOURCE_IDENTIFIERS_HPP

namespace sf
{
class Texture;
class Font;
}

enum class Textures
{
  TITLE_BG,
};

enum class Fonts
{
  MONOSPACE,
  GREENSCREEN,
  MANASPACE,
  PRESS_START_2P,
  SDS_8BIT,
};

enum class Music
{
  MENU_THEME,
  GAME_THEME,
};

template <typename Resource, typename Identifier>
class ResourceCache;

typedef ResourceCache<sf::Texture, Textures> TextureCache;
typedef ResourceCache<sf::Font, Fonts> FontCache;

#endif
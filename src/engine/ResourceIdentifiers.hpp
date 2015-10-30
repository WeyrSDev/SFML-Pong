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
  SDS_8BIT,
  C64_Pixel,
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
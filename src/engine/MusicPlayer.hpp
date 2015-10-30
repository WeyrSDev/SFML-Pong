#ifndef MUSICPLAYER_HPP
#define MUSICPLAYER_HPP

#include "ResourceIdentifiers.hpp"
#include <SFML/Audio/Music.hpp>
#include <map>


class MusicPlayer
{
public:
  MusicPlayer();
  void play( Music theme );
  void stop();
  void pause();
  void resume();
  void setVolume( float volume );

private:
  sf::Music mMusic;
  std::map<Music, std::string> mMusicFiles;
  float mVolume;

  MusicPlayer( const MusicPlayer& ) = delete;
  MusicPlayer& operator=( const MusicPlayer& ) = delete;
};

#endif
#include "MusicPlayer.hpp"

MusicPlayer::MusicPlayer()
  : mMusic()
  , mMusicFiles()
  , mVolume( 100u )
{
  mMusicFiles[ Music::MENU_THEME ] = "";
  mMusicFiles[ Music::GAME_THEME ] = "";
}

void MusicPlayer::play( Music theme )
{
  std::string file = mMusicFiles[ theme ];

  if( !mMusic.openFromFile( file ) ) {
    throw std::runtime_error( "" );
  }

  mMusic.setVolume( mVolume );
  mMusic.setLoop( true );
  mMusic.play();
}

void MusicPlayer::stop()
{
  mMusic.stop();
}

void MusicPlayer::pause()
{
  mMusic.pause();
}

void MusicPlayer::resume()
{
  mMusic.play();
}

void MusicPlayer::setVolume( const float volume )
{
  mVolume = volume;
}
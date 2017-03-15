#include "MusicPlayer.hpp"
#include "Context.hpp"

namespace core {

MusicPlayer::MusicPlayer( Context* context )
  : mMusic()
  , mVolume( 100u )
  , mContext( context )
{}

void MusicPlayer::play( Music theme ) {
  //std::string file = mMusicFiles[ theme ];

  std::string file = mContext->music->find( theme )->second;

  if( !mMusic.openFromFile( file )) {
    throw std::runtime_error( "" );
  }

  mMusic.setVolume( mVolume );
  mMusic.setLoop( true );
  mMusic.play();
}

void MusicPlayer::stop() {
  mMusic.stop();
}

void MusicPlayer::pause() {
  mMusic.pause();
}

void MusicPlayer::resume() {
  mMusic.play();
}

void MusicPlayer::setVolume( float volume ) {
  if( volume > 100.f ){
    volume = 100.f;
  }

  mVolume = volume;
}

} // end namespace core
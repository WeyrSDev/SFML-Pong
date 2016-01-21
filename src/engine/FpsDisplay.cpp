#include "FpsDisplay.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

namespace core
{
// Hidden implementation class of FpsDisplay
// constructor must be called by contructor of FpsDisplay
class FpsDisplay::Impl
{
public:
  Impl( const sf::Font& font, unsigned int size );
  void update( const sf::Time dt );

  sf::Text mFpsText;
  sf::Time mFpsTime;
  std::size_t mFrames;
  std::size_t mFps;
};

///////////////////////////////////////////////////////////////////////////////

FpsDisplay::Impl::Impl( const sf::Font& font, unsigned int size )
  : mFpsText( "0 fps", font, size )
  , mFpsTime( sf::Time::Zero )
  , mFrames( 0 )
  , mFps( 0 )  
{}

///////////////////////////////////////////////////////////////////////////////

void FpsDisplay::Impl::update( const sf::Time dt )
{
  mFpsTime += dt;
  mFrames += 1;

  if( mFpsTime > sf::seconds( 1.f ) ) {
    mFps = mFrames;
    mFrames = 0;
    mFpsTime -= sf::seconds( 1.f );
    mFpsText.setString( std::to_string( mFps ) + " fps" );
  }
}

///////////////////////////////////////////////////////////////////////////////

FpsDisplay::FpsDisplay( const sf::Font& font, unsigned int size )
  : mImpl( std::make_unique<Impl>( font, size ) )
{}

///////////////////////////////////////////////////////////////////////////////

// explicit default destructor is needed that the unique_ptr-member
// can be deconstructed, defaulting doesn't work here
//FpsDisplay::~FpsDisplay()
//{}

///////////////////////////////////////////////////////////////////////////////

void FpsDisplay::update( const sf::Time dt )
{
  mImpl->update( dt );
}

///////////////////////////////////////////////////////////////////////////////

// Implementation of draw does not need to reside in FpsDisplay::Impl
// because virtual functions should be defined in the visible class
void FpsDisplay::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
  states.transform *= getTransform();
  target.draw( mImpl->mFpsText, states );
}

///////////////////////////////////////////////////////////////////////////////

} // end namespace core
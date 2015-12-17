#include "CreditState.hpp"
#include <engine/Utility.hpp>
#include <engine/Context.hpp>
#include <engine/Blackboard.hpp>
#include <engine/ResourceCache.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <fstream>
#include <sstream>

CreditState::CreditState( StateStack & stack, States id )
  : State( stack, id )
{
  auto winSize = getContext()->window->getView().getSize();
  auto bgSprite = std::make_unique<sf::Sprite>
    ( getContext()->textures->get( Textures::TITLE_BG ) );
  mDrawObjects.push_back( std::move( bgSprite ) );

  auto statusText = std::make_unique<sf::Text>
    ( "Press ESC to return to menu",
      getContext()->fonts->get( Fonts::DP_COMIC ),
      24u );
  util::centerOrigin( *statusText );
  statusText->setPosition( winSize.x / 2.f, winSize.y - 30.f );
  mDrawObjects.push_back( std::move( statusText ) );

  std::string creditsFilename { "../media/credits.txt" };
  std::ifstream creditsFile( creditsFilename );
  if( !creditsFile.is_open() ) {
    throw std::runtime_error( "Error opening file " + creditsFilename );
  }
  std::stringstream content;
  content << creditsFile.rdbuf();
  creditsFile.close();
  sf::String creditsText = content.str();

  auto credits = std::make_unique<sf::Text>
    ( creditsText,
      getContext()->fonts->get( Fonts::MONOSPACE ),
      18u );
  util::centerOrigin( *credits );
  credits->setPosition( winSize / 2.f );
  mDrawObjects.push_back( std::move( credits ) );
}

bool CreditState::handleInput( const sf::Event & event )
{
  if( event.type == getContext()->blackboard->keyEventType ) {
    if( event.key.code == sf::Keyboard::Escape ) {
      requestStackPop();
    }    
  }

  return false;
}

bool CreditState::update( sf::Time dt )
{
  return false;
}

void CreditState::render()
{
  sf::RenderWindow& window = *getContext()->window;
  for( const auto& drawObject : mDrawObjects ) {
    window.draw( *drawObject );
  }
}

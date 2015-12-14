#include "CreditState.hpp"
#include <engine/Context.hpp>
#include <engine/ResourceCache.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

CreditState::CreditState( StateStack & stack, States id )
  : State( stack, id )
{
  auto winSize = getContext()->window->getView().getSize();
  auto bgSprite = std::make_unique<sf::Sprite>
    ( getContext()->textures->get( Textures::TITLE_BG ) );
  mDrawObjects.push_back( std::move( bgSprite ) );
}

bool CreditState::handleInput( const sf::Event & event )
{
  if( event.type == sf::Event::KeyReleased ) {
    requestStackPop();
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

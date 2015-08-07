#include <pong/GameWorld.hpp>
#include <pong/Utility.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

GameWorld::GameWorld( const Context& context )
  : mContext( context )
  , mPlayer( { 20.f, 100.f } )
  , mEnemy( { 20.f, 100.f } )
  , mGameBall( 10.f )
  , mMoveUp( false )
  , mMoveDown( false )
  , mPlayerSpeed( 200.f )
  , mBallAngle( 0 )
  , mBallStartSpeed( 50.f )
  , mBallSpeed( mBallStartSpeed )
  , mEnemySpeed( 200.f )
{
  sf::Vector2f winSize{ static_cast<float>( context.window->getSize().x ),
                        static_cast<float>( context.window->getSize().y ) };
  mPlayer.setFillColor( sf::Color::Green );
  mPlayer.setOrigin( mPlayer.getSize() / 2.f );
  mPlayer.setPosition( mPlayer.getOrigin().x, winSize.y / 2.f );

  mEnemy.setFillColor( sf::Color::Green );
  mEnemy.setOrigin( mEnemy.getSize() / 2.f );
  mEnemy.setPosition( winSize.x - mEnemy.getOrigin().x, winSize.y / 2.f );

  mGameBall.setFillColor( sf::Color::Green );
  mGameBall.setOrigin( mGameBall.getRadius(), mGameBall.getRadius() );
  mGameBall.setPosition( winSize / 2.f );

  mBallAngle = util::randomInt( 50, 70 );
  std::cout << "ball starting angle " << mBallAngle << std::endl;
}

void GameWorld::handleEvents( const sf::Event& event )
{
  if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ) {
    mMoveUp = true; // generate move up command
  }
  if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) ) {
    mMoveDown = true; // generate move down command
  }
}

void GameWorld::update( const sf::Time dt )
{
  auto winSize = sf::Vector2f{ static_cast<float>( mContext.window->getSize().x ),
                               static_cast<float>( mContext.window->getSize().y ) };
  auto vector = util::toVector( util::degToRad( static_cast<float>( mBallAngle ) ) );
  auto ballMove = vector * mBallSpeed * dt.asSeconds();
  auto ballGBounds = mGameBall.getGlobalBounds();

  // if ball would move out of window correct the movement to just hit the wall
  // not only the y-value but also the x-value of the collision step must be corrected
  // this uses sin-sentence to calculate the new x- and y- movement coordinates
  if( ballGBounds.top + ballMove.y <= 0.f ) {
    float c = ballGBounds.top;
    auto beta = 360.f - ( static_cast<float>( mBallAngle ) + 90.f );
    auto gamma = 90.f - beta;
    auto b_new = std::sin( util::degToRad( beta ) ) *
                 ( c / std::sin( util::degToRad( gamma ) ) );
    ballMove.x = -b_new;
    ballMove.y = -c;
    mGameBall.move( ballMove );
    mBallAngle = 360 - mBallAngle;
  } else if( ballGBounds.top + ballGBounds.height + ballMove.y >= winSize.y ) {
    float c = winSize.y - ( ballGBounds.top + ballGBounds.height );
    auto gamma = 90.f - ( static_cast<float>( mBallAngle ) - 90.f );
    auto a_new = c / std::sin( util::degToRad( gamma ) );
    ballMove.x = -a_new;
    ballMove.y = c;
    mGameBall.move( ballMove );
    mBallAngle = 360 - mBallAngle;
  } else if( ballGBounds.intersects(mPlayer.getGlobalBounds() ) ) {

  } else if( ballGBounds.intersects(mEnemy.getGlobalBounds() ) ) {

  } else {
    mGameBall.move( ballMove );
  }

  // move player paddle
  // pre calculate the target of movement before actual movement
  // to make correct collision detection with top and bottom of window
  auto playerMove = mPlayerSpeed * dt.asSeconds();
  auto playerGBounds = mPlayer.getGlobalBounds();  
  if( mMoveUp ) {
    if( playerGBounds.top - playerMove <= 0.f ) {
      mPlayer.move( 0.f, -playerGBounds.top );
      mMoveUp = false;
    } else {
      mPlayer.move( 0.f, -playerMove );
      mMoveUp = false;
    }
  }
  if( mMoveDown ) {
    if( playerGBounds.top + playerGBounds.height >= winSize.y ) {
      auto curYDistance = winSize.y - ( playerGBounds.top + playerGBounds.height );
      mPlayer.move( 0.f, curYDistance );
      mMoveDown = false;
    } else {
      mPlayer.move( 0.f, playerMove );
      mMoveDown = false;
    }
  }  

  // move enemy paddle
  // same pre calculation as for player paddle
  // movement depends on ball position
  // possible alternative is to move paddle to center when ball flies in players direction
  auto enemyMove = mEnemySpeed * dt.asSeconds();
  auto enemyGBounds = mEnemy.getGlobalBounds();
  if( mGameBall.getPosition().y < mEnemy.getPosition().y ) {
    if( enemyGBounds.top - enemyMove <= 0.f ) {
      mEnemy.move( 0.f, -enemyGBounds.top );
    } else {
      mEnemy.move( 0.f, -enemyMove );
    }
  }
  if( mGameBall.getPosition().y > mEnemy.getPosition().y ) {
    if( enemyGBounds.top + enemyGBounds.height >= winSize.y ) {
      mEnemy.move( 0.f, winSize.y - ( enemyGBounds.top + enemyGBounds.height ) );
    } else {
      mEnemy.move( 0.f, enemyMove );
    }    
  }
}

void GameWorld::draw()
{
  sf::RenderWindow& window = *mContext.window;
  window.draw( mPlayer );
  window.draw( mEnemy );
  window.draw( mGameBall );
}
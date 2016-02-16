#include "GameWorld.hpp"
#include <engine/Utility.hpp>
#include <engine/Context.hpp>
#include <game/Blackboard.hpp>
#include <game/ResourceIdentifiers.hpp>
#include <engine/ResourceCache.hpp>
#include <engine/LogSystem.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#ifdef _DEBUG
#include <iostream>
#endif

///////////////////////////////////////////////////////////////////////////////

GameWorld::GameWorld( const core::Context& context )
  : mContext( context )
  , mWinSize()
  , mPlayer( Paddle::Type::Player, context )
  , mEnemy( Paddle::Type::Computer, context )
  //, mGameBall( 10.f )
  , mGameBall( context )
  , mMoveUp( false )
  , mMoveDown( false )
  , mPlayerSpeed( 200.f )
  , mBallAngle( 0 )
  , mBallStartSpeed( 200.f )
  , mBallSpeed( mBallStartSpeed )
  , mOldBallSpeed( 0.f )
  , mBallAcceleration( 25.f )
  , mEnemySpeed( 200.f )
  , mPlayerScore( 0u )
  , mEnemyScore( 0u )
  , mScoreText()
  , mGameTime( sf::Time::Zero )
  , mWinScore( 2u )  
#ifdef _DEBUG
  , mStopBallMove( false )
  , mSingleFrameStep( false )
  , mSingleFrameMode( false )
  , mShowDebugInfo( true )
  , mDebugInfo()
  , mDebugTimer( sf::Time::Zero )
#endif
{
  mWinSize = { static_cast<float>( context.window->getSize().x ),
               static_cast<float>( context.window->getSize().y ) };
  mPlayer.setColor( sf::Color::Green );  
  core::centerOrigin( mPlayer );
  mPlayer.setPosition( mPlayer.getOrigin().x + 10.f, mWinSize.y / 2.f );
  mPlayer.setScale( sf::Vector2f { 1.5f, 1.5f } );
  
  mEnemy.setColor( sf::Color::Green );
  core::centerOrigin( mEnemy );
  mEnemy.setPosition( mWinSize.x - mEnemy.getOrigin().x -10.f, mWinSize.y / 2.f );
  mEnemy.setScale( sf::Vector2f { 1.5f, 1.5f } );

  mGameBall.setColor( sf::Color::Green );
  core::centerOrigin( mGameBall );
  mGameBall.setScale( sf::Vector2f { 1.5f, 1.5f } );
  resetGameBall();

  mScoreText.setFont( mContext.fonts->get( Fonts::C64_Pixel ) );
  mScoreText.setCharacterSize( 30u );
  mScoreText.setColor( sf::Color::Green );
  setScoreString();
  core::centerOrigin( mScoreText );
  mScoreText.setPosition( mWinSize.x / 2.f, mScoreText.getOrigin().y + 5.f );

#ifdef _DEBUG
  mDebugInfo.setFont( mContext.fonts->get( Fonts::MONOSPACE ) );
  mDebugInfo.setCharacterSize( 10u );
  //setDebugInfo( dt );
  mDebugInfo.setPosition( 15.f, mWinSize.y - 15.f );
  //std::cout << core::dumpToString( mPlayer ) << std::endl;
  mContext.log->write( "Debug dump of player variables\n" + core::dumpToString( mPlayer ),
                       core::LogType::DEBUG );
  mContext.log->write( "Debug dump of enemy variables\n" + core::dumpToString( mEnemy ),
                       core::LogType::DEBUG );
#endif
  
  mContext.log->write( "GameWorld initialized successfully", core::LogType::DEBUG );
}

///////////////////////////////////////////////////////////////////////////////

void GameWorld::handleInput( const sf::Event& event )
{
  if( event.type == mContext.blackboard->keyEventType ) {
#ifdef _DEBUG
    if( event.key.code == sf::Keyboard::F1 ) {
      mShowDebugInfo = !mShowDebugInfo; // toggle debug info on/off
      mContext.log->write( "Show debug info set to " + std::to_string( mShowDebugInfo ),
                           core::LogType::DEBUG );
    }
    if( event.key.code == sf::Keyboard::F2 ) {
      mStopBallMove = !mStopBallMove; // toggle ball movement
      mContext.log->write( "Stop ball set to " + std::to_string( mStopBallMove ),
                           core::LogType::DEBUG );
    }    
    if( event.key.code == sf::Keyboard::F3 ) {
      mSingleFrameMode = !mSingleFrameMode; // toggle single frame mode on/off
      mContext.log->write( "Single frame mode set to " + std::to_string( mSingleFrameMode ),
                           core::LogType::DEBUG );
    }
    if( event.key.code == sf::Keyboard::F4 ) {
      mSingleFrameStep = true; // advance a single frame in single frame mode
      mContext.log->write( "Single frame mode next step", core::LogType::DEBUG );
    }
    if( event.key.code == sf::Keyboard::F5 ) {
      // insta win game to move to gameover screen
      mContext.blackboard->playerWon = true;
      mContext.blackboard->gameOver = true;
      mContext.log->write( "Insta win triggered by user", core::LogType::DEBUG );
    }
    if( event.key.code == sf::Keyboard::F6 ) {
      // insta loose to move to gameover screen
      mContext.blackboard->playerWon = false;
      mContext.blackboard->gameOver = true;
      mContext.log->write( "Insta loss triggered by user", core::LogType::DEBUG );
    }
#endif
  }
}

///////////////////////////////////////////////////////////////////////////////

void GameWorld::handleRealtimeInput()
{
  if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ) {
    mMoveUp = true; // generate move up command
  }
  if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) ) {
    mMoveDown = true; // generate move down command
  }
}

///////////////////////////////////////////////////////////////////////////////

void GameWorld::update( const sf::Time dt )
{
#ifdef _DEBUG
  // if debug info is to be shown, update it before hand
  if( mShowDebugInfo ) {
    setDebugInfo( dt );
  }
  // if we are in single frame mode and no single frame step has been requested
  // just abort update completly, so nothing happens
  // otherwise continue and reset single frame step variable
  if( mSingleFrameMode && !mSingleFrameStep ) {
    return;
  }
  mSingleFrameStep = false;

  if( mStopBallMove ) {
    if( mBallSpeed != 0.f ) {
      mOldBallSpeed = mBallSpeed;
      mBallSpeed = 0.f;
    }
  } else {
    if( mOldBallSpeed != 0.f ) {
      mBallSpeed = mOldBallSpeed;
      mOldBallSpeed = 0.f;
    }
  }
#endif

  mGameTime += dt; // count the elapsed time of the played ball
  if( mGameTime < sf::seconds( 2.0f ) ) {
    return; // if not 2 seconds have passed immediatly cancel update
  }

  auto vector = core::toVector( core::degToRad( static_cast<float>( mBallAngle ) ) );
  auto ballMove = vector * mBallSpeed * dt.asSeconds();
  auto ballGBounds = mGameBall.getGlobalBounds();
  const auto playerGBounds = mPlayer.getGlobalBounds();
  const auto ballRadius = mGameBall.getGlobalBounds().width / 2.f;

  // if ball would move out of window correct the movement to just hit the wall
  // not only the y-value but also the x-value of the collision step must be corrected
  // this uses sine sentence to calculate the new x- and y-movement coordinates
  // after position is corrected ball angle has to be reflected at x-axis
  // formula for x-axis reflection is newAngle = 360 - oldAngle  
  if( ballGBounds.top + ballMove.y <= 0.f ) {
    float c = ballGBounds.top;
    auto beta = 360.f - ( static_cast<float>( mBallAngle ) + 90.f );
    auto gamma = 90.f - beta;
    auto b_new = std::sin( core::degToRad( beta ) ) *
                 ( c / std::sin( core::degToRad( gamma ) ) );
    ballMove.x = -b_new;
    ballMove.y = -c;
    mGameBall.move( ballMove );
    mBallAngle = 360 - mBallAngle;
  } else if( ballGBounds.top + ballGBounds.height + ballMove.y >= mWinSize.y ) {
    float c = mWinSize.y - ( ballGBounds.top + ballGBounds.height );
    auto gamma = 90.f - ( static_cast<float>( mBallAngle ) - 90.f );
    auto a_new = c / std::sin( core::degToRad( gamma ) );
    ballMove.x = -a_new;
    ballMove.y = c;
    mGameBall.move( ballMove );
    mBallAngle = 360 - mBallAngle;
  } 
  // if the ball collides with one of the paddles correct x position to just
  // touch the paddle and reflect ball a y-axis
  // formula for y-axis reflection is newAngle = 360 + ( 180 - oldAngle )
  // speed ball up by acceleration after every paddle collision
  // TODO: detect where the paddle is hit for correct physical reflection
  else if( ballGBounds.intersects( mPlayer.getGlobalBounds() )
           && mBallAngle > 90 && mBallAngle < 270 ) {
    auto newBallX = playerGBounds.left + playerGBounds.width
                    + ballRadius;
    mGameBall.setPosition( newBallX, mGameBall.getPosition().y );
    mBallSpeed += mBallAcceleration;
    // adding a friction to the ball based on paddle movement
    if( mBallAngle < 180 && mMoveUp ) {
      mBallAngle = 360 + ( 180 - mBallAngle ) - core::randomInt( 5, 10 );
    } else if( mBallAngle < 180 && mMoveDown ) {
      mBallAngle = 360 + ( 180 - mBallAngle ) + core::randomInt( 5, 10 );
    } else if( mBallAngle > 180 && mMoveUp ) {
      mBallAngle = 360 + ( 180 - mBallAngle ) - core::randomInt( 5, 10 );
    } else if( mBallAngle >180 && mMoveDown ) {
      mBallAngle = 360 + ( 180 - mBallAngle ) + core::randomInt( 5, 10 );
    } else {
      mBallAngle = 360 + ( 180 - mBallAngle );
    }
  } else if( ballGBounds.intersects( mEnemy.getGlobalBounds() ) ) {
    auto newBallX = mEnemy.getGlobalBounds().left - ballRadius;
    mGameBall.setPosition( newBallX, mGameBall.getPosition().y );
    mBallAngle = 360 + ( 180 - mBallAngle );
    mBallSpeed += mBallAcceleration;
  } else {
    mGameBall.move( ballMove );
  }

  // after all modifications to ball angle normalize it to be between 0 and 360
  mBallAngle = core::normalizeAngle( mBallAngle );

  // move player paddle
  // pre calculate the target of movement before actual movement
  // to make correct collision detection with top and bottom of window
  auto playerMove = mPlayerSpeed * dt.asSeconds(); // always positive value
  if( mMoveUp ) {
    playerMove = -playerMove; // negate to simulate upper movement
    //mContext.log->write( "playerMove=" + std::to_string( playerMove ), core::LogType::DEBUG );
    if( playerGBounds.top + playerMove <= 0.f ) {
      mPlayer.move( 0.f, -playerGBounds.top );
      mMoveUp = false;
    } else {
      mPlayer.move( 0.f, playerMove );
      mMoveUp = false;
    }
  }
  if( mMoveDown ) {
    //mContext.log->write( "playerMove=" + std::to_string( playerMove ), core::LogType::DEBUG );
    if( playerGBounds.top + playerGBounds.height >= mWinSize.y ) {
      auto curYDistance = mWinSize.y - ( playerGBounds.top
                                         + playerGBounds.height );
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
  // possible alternative is to move paddle to center when
  // ball flies in players direction
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
    if( enemyGBounds.top + enemyGBounds.height >= mWinSize.y ) {
      mEnemy.move( 0.f, mWinSize.y - ( enemyGBounds.top
                                       + enemyGBounds.height ) );
    } else {
      mEnemy.move( 0.f, enemyMove );
    }    
  }

  // check for scoring
  if( mGameBall.getPosition().x + ballRadius < 0.f ) {
    mEnemyScore += 1;
    setScoreString();
    resetGameBall();
  } else if( mGameBall.getPosition().x - ballRadius > mWinSize.x ) {
    mPlayerScore += 1;
    setScoreString();
    resetGameBall();
  }

  // check for win condition and set flags in blackboard
  if( mPlayerScore >= mWinScore && mPlayerScore >= mEnemyScore ) {
    mContext.blackboard->gameOver = true;
    mContext.blackboard->playerWon = true;
  } else if( mEnemyScore >= mWinScore && mEnemyScore >= mPlayerScore ) {
    mContext.blackboard->gameOver = true;
    mContext.blackboard->playerWon = false;
  }  
}

///////////////////////////////////////////////////////////////////////////////

void GameWorld::render()
{
  sf::RenderWindow& window = *mContext.window;
  window.draw( mScoreText );
  window.draw( mPlayer );
  window.draw( mEnemy );
  window.draw( mGameBall );

#ifdef _DEBUG
  if( mShowDebugInfo ) {
    window.draw( mDebugInfo );
  }
#endif
}

///////////////////////////////////////////////////////////////////////////////

void GameWorld::setScoreString()
{
  mScoreText.setString( std::to_string( mPlayerScore ) + " : "
                        + std::to_string( mEnemyScore ) );
}

///////////////////////////////////////////////////////////////////////////////

void GameWorld::resetGameBall()
{  
  mContext.log->write( "GameWorld::resetGameBall called", core::LogType::DEBUG );

  mGameBall.setPosition( mWinSize / 2.f );
  mBallAngle = core::randomInt( 135, 225 );
  if( mBallAngle > 170 && mBallAngle < 190 ) {
    if( mBallAngle < 180 ) {
      mBallAngle -= core::randomInt( 7, 12 );
    } else {
      mBallAngle += core::randomInt( 7, 12 );
    }
  }
  mBallSpeed = mBallStartSpeed;
  mGameTime = sf::Time::Zero;
  mPlayer.setPosition( mPlayer.getPosition().x, mWinSize.y / 2.f );
  mEnemy.setPosition( mEnemy.getPosition().x, mWinSize.y / 2.f );
}

///////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
void GameWorld::setDebugInfo( sf::Time dt )
{
  mDebugTimer += dt;

  if( mDebugTimer > sf::seconds( 0.1f ) ) {
    mDebugInfo.setString( "player paddle x: " + std::to_string(mPlayer.getPosition().x )
                          + " y: " + std::to_string(mPlayer.getPosition().y) + "\n"
                          + "game ball x: " + std::to_string( mGameBall.getPosition().x )
                          + " y: " + std::to_string( mGameBall.getPosition().y ) + "\n"
                          + "ball speed: " + std::to_string( mBallSpeed )
                          + " ball angle: " + std::to_string( mBallAngle ) + "\n"
                          + "game time: " + std::to_string( mGameTime.asSeconds() )
                          );

    // set origin to lower left corner
    mDebugInfo.setOrigin( 0.f, mDebugInfo.getLocalBounds().height );

    mDebugTimer = sf::Time::Zero;
  }
}
#endif

///////////////////////////////////////////////////////////////////////////////
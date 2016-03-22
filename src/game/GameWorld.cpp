#include "GameWorld.hpp"
#include <engine/Utility.hpp>
#include <engine/Context.hpp>
#include <game/Blackboard.hpp>
#include <game/ResourceIdentifiers.hpp>
#include <engine/ResourceCache.hpp>
#include <engine/LogSystem.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

///////////////////////////////////////////////////////////////////////////////

GameWorld::GameWorld( const core::Context& context )
  : mContext( context )
  , mWinSize()
  , mPlayer( Paddle::Type::Player, &mContext )
  , mEnemy( Paddle::Type::Computer, &mContext )
  , mGameBall( &mContext )
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
  , mBallTime( sf::Time::Zero )
  , mGameTime( sf::Time::Zero )
  , mDT( sf::Time::Zero )
  , mWinScore( 100u )
  , mScaleFactor( 1.5f )
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
  mPlayer.setScale( sf::Vector2f{ mScaleFactor, mScaleFactor } );

  mEnemy.setColor( sf::Color::Green );
  core::centerOrigin( mEnemy );
  mEnemy.setPosition( mWinSize.x - mEnemy.getOrigin().x - 10.f, mWinSize.y / 2.f );
  mEnemy.setScale( sf::Vector2f{ mScaleFactor, mScaleFactor } );

  mGameBall.setColor( sf::Color::Green );
  core::centerOrigin( mGameBall );
  mGameBall.setScale( sf::Vector2f{ mScaleFactor, mScaleFactor } );
  resetGameBall();

  mScoreText.setFont( mContext.fonts->get( Fonts::C64 ) );
  mScoreText.setCharacterSize( 30u );
  mScoreText.setColor( sf::Color::Green );
  setScoreString();
  core::centerOrigin( mScoreText );
  mScoreText.setPosition( mWinSize.x / 2.f, mScoreText.getOrigin().y + 5.f );

  #ifdef _DEBUG
  mDebugInfo.setFont( mContext.fonts->get( Fonts::MONOSPACE ) );
  mDebugInfo.setCharacterSize( 8u );
  mDebugInfo.setPosition( 15.f, mWinSize.y - 15.f );
  mContext.log->write( "Debug draw mode set to " + std::to_string( mShowDebugInfo ),
                       core::LogType::DEBUG );
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
      mShowDebugInfo = !mShowDebugInfo; // toggle debug draw on/off
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
    setDebugInfo();
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

  mPlayer.setDebugDraw( mShowDebugInfo );
  mEnemy.setDebugDraw( mShowDebugInfo );
  mGameBall.setDebugDraw( mShowDebugInfo );

  #endif

  mDT = dt;
  mBallTime += dt; // count the elapsed time of the played ball
  mGameTime += dt; // count total elapsed time of the game
  if( mBallTime < sf::seconds( 2.0f ) ) {
    return; // if not 2 seconds have passed immediatly cancel update
  }

  // set all velocities to zero and do the next simulation step
  sf::Vector2f zero{ 0.f, 0.f };
  mGameBall.setVelocity( zero );
  mPlayer.setVelocity( zero );
  mEnemy.setVelocity( zero );

  // check for upcoming collisions and set resulting velocities
  handleCollisions( dt );

  // update all entities
  updateEntities( dt );

  checkForScoring();

  checkForGameover();
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

void GameWorld::handleCollisions( const sf::Time& dt )
{
  const auto direction = core::toVector( core::degToRad( static_cast<float>( mBallAngle ) ) );
  auto ballVelocity = direction * mBallSpeed * mDT.asSeconds();
  const auto ballGBounds = mGameBall.getGlobalBounds();
  const auto ballTopY = ballGBounds.top + ballVelocity.y;
  const auto ballBotY = ballGBounds.top + ballGBounds.height + ballVelocity.y;
  const auto ballRadius = ballGBounds.width / 2.f;
  const auto playerGBounds = mPlayer.getGlobalBounds();

  // ball - top collision
  // if top is lower than 0, flip the y-coord of ball velocity vector
  if( ballTopY < 0.f ) {
    ballVelocity.y = -ballTopY;
    mGameBall.setVelocity( ballVelocity );
    mBallAngle = 360 - mBallAngle;
  }

  // ball - bottom collision
  // if bottom is greater than window size, flip the y-coord of ball velocity vector
  else if( ballBotY > mWinSize.y ) {
    ballVelocity.y = - ( ballBotY - mWinSize.y );
    mContext.log->write( std::to_string( ballVelocity.y ), core::LogType::DEBUG );
    mGameBall.setVelocity( ballVelocity );
    mBallAngle = 360 - mBallAngle;
  }

  // ball - left paddle collision
  else if( ballGBounds.intersects( mPlayer.getGlobalBounds() )
           && mBallAngle > 90 && mBallAngle < 270 ) {
    auto newBallX = playerGBounds.left + playerGBounds.width + ballRadius;
    mGameBall.setPosition( newBallX, mGameBall.getPosition().y );
    mBallAngle = 360 + ( 180 - mBallAngle );
    mBallSpeed += mBallAcceleration;
  }

  // ball - right paddle collision
  else if( ballGBounds.intersects( mEnemy.getGlobalBounds() ) ) {
    auto newBallX = mEnemy.getGlobalBounds().left - ballRadius;
    mGameBall.setPosition( newBallX, mGameBall.getPosition().y );
    mBallAngle = 360 + ( 180 - mBallAngle );
    mBallSpeed += mBallAcceleration;
  } else {
    mGameBall.setVelocity( ballVelocity );
  }

  mBallAngle = core::normalizeAngle( mBallAngle );

  // left paddle - top/bottom collision
  auto playerYVelocity = mPlayer.getSpeed() * dt.asSeconds(); //always positive value
  if( mMoveUp ) {
    playerYVelocity = -playerYVelocity; // negate to simulate upper movement
    if( playerGBounds.top + playerYVelocity <= 0.f ) {
      //mPlayer.move( 0.f, -playerGBounds.top );
      mPlayer.setVelocity( sf::Vector2f( 0.f, -playerGBounds.top ) );
      mMoveUp = false;
    } else {
      //mPlayer.move( 0.f, playerYVelocity );
      mPlayer.setVelocity( sf::Vector2f( 0.f, playerYVelocity ) );
      mMoveUp = false;
    }
  }
  if( mMoveDown ) {
    if( playerGBounds.top + playerGBounds.height >= mWinSize.y ) {
      auto curYDistance = mWinSize.y - ( playerGBounds.top
                                         + playerGBounds.height );
      mPlayer.setVelocity( sf::Vector2f( 0.f, curYDistance ) );
      mMoveDown = false;
    } else {
      mPlayer.setVelocity( sf::Vector2f( 0.f, playerYVelocity ) );
      mMoveDown = false;
    }
  }

  // right paddle movement and top/bottom collision
  auto enemyYVelocity = mEnemy.getSpeed() * dt.asSeconds(); // always positive value
  const auto enemyGBounds = mEnemy.getGlobalBounds();
  if( mGameBall.getPosition().y < mEnemy.getPosition().y ) {
    if( enemyGBounds.top - enemyYVelocity <= 0.f ) {
      mEnemy.setVelocity( sf::Vector2f{ 0.f,-enemyGBounds.top } );
    } else {
      mEnemy.setVelocity( sf::Vector2f{ 0.f, -enemyYVelocity } );
    }
  }
  if( mGameBall.getPosition().y > mEnemy.getPosition().y ) {
    if( enemyGBounds.top + enemyGBounds.height >= mWinSize.y ) {
      auto curYDistance = mWinSize.y - ( enemyGBounds.top + enemyGBounds.height );
      mEnemy.setVelocity( sf::Vector2f{ 0.f, curYDistance } );
    } else {
      mEnemy.setVelocity( sf::Vector2f{ 0.f, enemyYVelocity } );
    }
  }
}

///////////////////////////////////////////////////////////////////////////////

void GameWorld::updateEntities( const sf::Time& dt )
{
  mGameBall.update( dt );
  mPlayer.update( dt );
  mEnemy.update( dt );
}

/////////////////////////////////////////////////////////////////////////////////
//
//void GameWorld::movePlayer()
//{
//  // move player paddle
//  // pre calculate the target of movement before actual movement
//  // to make correct collision detection with top and bottom of window
//  auto playerMove = mPlayerSpeed * mDT.asSeconds(); // always positive value
//  const auto playerGBounds = mPlayer.getGlobalBounds();
//
//  if( mMoveUp ) {
//    playerMove = -playerMove; // negate to simulate upper movement
//    //mContext.log->write( "playerMove=" + std::to_string( playerMove ), core::LogType::DEBUG );
//    if( playerGBounds.top + playerMove <= 0.f ) {
//      mPlayer.move( 0.f, -playerGBounds.top );
//      mMoveUp = false;
//    } else {
//      mPlayer.move( 0.f, playerMove );
//      mMoveUp = false;
//    }
//  }
//  if( mMoveDown ) {
//    //mContext.log->write( "playerMove=" + std::to_string( playerMove ), core::LogType::DEBUG );
//    if( playerGBounds.top + playerGBounds.height >= mWinSize.y ) {
//      auto curYDistance = mWinSize.y - ( playerGBounds.top
//                                         + playerGBounds.height );
//      mPlayer.move( 0.f, curYDistance );
//      mMoveDown = false;
//    } else {
//      mPlayer.move( 0.f, playerMove );
//      mMoveDown = false;
//    }
//  }
//}
//
/////////////////////////////////////////////////////////////////////////////////
//
//void GameWorld::moveEnemy()
//{
//  // move enemy paddle
//  // same pre calculation as for player paddle
//  // movement depends on ball position
//  // possible alternative is to move paddle to center when
//  // ball flies in players direction
//  auto enemyMove = mEnemySpeed * mDT.asSeconds();
//  const auto enemyGBounds = mEnemy.getGlobalBounds();
//  if( mGameBall.getPosition().y < mEnemy.getPosition().y ) {
//    if( enemyGBounds.top - enemyMove <= 0.f ) {
//      mEnemy.move( 0.f, -enemyGBounds.top );
//    } else {
//      mEnemy.move( 0.f, -enemyMove );
//    }
//  }
//  if( mGameBall.getPosition().y > mEnemy.getPosition().y ) {
//    if( enemyGBounds.top + enemyGBounds.height >= mWinSize.y ) {
//      mEnemy.move( 0.f, mWinSize.y - ( enemyGBounds.top
//                   + enemyGBounds.height ) );
//    } else {
//      mEnemy.move( 0.f, enemyMove );
//    }
//  }
//}
//
///////////////////////////////////////////////////////////////////////////////

void GameWorld::checkForScoring()
{
  const auto ballBox = mGameBall.getGlobalBounds();

  // check for player scoring --> left side of ball > playfield right side
  if( ballBox.left > mWinSize.x ) {
    mPlayerScore += 1;
    mContext.log->write( "Player scored a goal, new score: "
                         + std::to_string( mPlayerScore ) + ":"
                         + std::to_string( mEnemyScore ),
                         core::LogType::INFO );
    setScoreString();
    resetGameBall();
  }

  // check for enemy scoring --> right side of ball < playfield left side
  if( ballBox.left + ballBox.width < 0.f ) {
    mEnemyScore += 1;
    mContext.log->write( "Computer scored a goal, new score: "
                         + std::to_string( mPlayerScore ) + ":"
                         + std::to_string( mEnemyScore ),
                         core::LogType::INFO );
    setScoreString();
    resetGameBall();
  }
}

///////////////////////////////////////////////////////////////////////////////

void GameWorld::checkForGameover()
{
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
  mBallTime = sf::Time::Zero;
  mPlayer.setPosition( mPlayer.getPosition().x, mWinSize.y / 2.f );
  mEnemy.setPosition( mEnemy.getPosition().x, mWinSize.y / 2.f );
}

///////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
void GameWorld::setDebugInfo()
{
  mDebugTimer += mDT;

  if( mDebugTimer > sf::seconds( 0.1f ) ) {
    mDebugInfo.setString( "ball speed: " + core::floatToString( mBallSpeed )
                          + "\tball angle: " + std::to_string( mBallAngle ) + "\n"
                          + "ball time: " + core::floatToString( mBallTime.asSeconds() )
                          + "\tgame time: " + core::floatToString( mGameTime.asSeconds() )
                          );


    // set origin to lower left corner
    mDebugInfo.setOrigin( 0.f, mDebugInfo.getLocalBounds().height );

    mDebugTimer = sf::Time::Zero;
  }
}
#endif

///////////////////////////////////////////////////////////////////////////////
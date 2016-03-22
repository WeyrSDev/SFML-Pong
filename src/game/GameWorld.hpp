#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP

#include "Paddle.hpp"
#include "GameBall.hpp"
#include <engine/Context.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class GameWorld
{
public:
  explicit GameWorld( const core::Context& context );
  void handleInput( const sf::Event& event );
  void handleRealtimeInput();
  void update( sf::Time dt );
  void render();

private:
  void handleCollisions( const sf::Time& dt );
  void updateEntities( const sf::Time& dt );
  void checkForScoring();
  void checkForGameover();
  void setScoreString();
  void resetGameBall();
#ifdef _DEBUG
  void setDebugInfo();
#endif

  core::Context mContext;
  sf::Vector2f mWinSize;
  Paddle mPlayer;
  Paddle mEnemy;
  GameBall mGameBall;
  bool mMoveUp;
  bool mMoveDown;
  float mPlayerSpeed;
  int mBallAngle;
  float mBallStartSpeed;
  float mBallSpeed;
  float mOldBallSpeed;
  float mBallAcceleration;
  float mEnemySpeed;
  unsigned int mPlayerScore;
  unsigned int mEnemyScore;
  sf::Text mScoreText;
  sf::Time mBallTime;
  sf::Time mGameTime;
  sf::Time mDT;
  unsigned int mWinScore;
  float mScaleFactor;

#ifdef _DEBUG
  bool mSingleFrameStep;
  bool mSingleFrameMode;
  bool mStopBallMove;
  bool mShowDebugInfo;
  sf::Text mDebugInfo;
  sf::Time mDebugTimer;
#endif
};

#endif
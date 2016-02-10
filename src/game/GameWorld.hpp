#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP

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
  void setScoreString();
  void resetGameBall();
#ifdef _DEBUG
  void setDebugInfo( sf::Time dt );
#endif

  core::Context mContext;
  sf::Vector2f mWinSize;
  sf::RectangleShape mPlayer;
  sf::RectangleShape mEnemy;
  sf::CircleShape mGameBall;
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
  sf::Time mGameTime;
  unsigned int mWinScore;
  
#ifdef _DEBUG
  bool mSingleFrameStep;
  bool mSingleFrameMode;
  bool mToggleBallMove;
  bool mShowDebugInfo;
  sf::Text mDebugInfo;
  sf::Time mDebugTimer;
#endif
};

#endif
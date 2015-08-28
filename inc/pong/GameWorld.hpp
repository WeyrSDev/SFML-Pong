#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP

#include "Context.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class GameWorld
{
public:
  explicit GameWorld( const Context& context );
  void handleEvents( const sf::Event& event );
  void update( sf::Time dt );
  void draw();

private:
  void setScoreString();
  void resetGameBall();

  Context mContext;
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
  float mBallAcceleration;
  float mEnemySpeed;
  unsigned int mPlayerScore;
  unsigned int mEnemyScore;
  sf::Font mFont;
  sf::Text mScoreText;
  bool mStopGameBall;
  bool mRestartGameBall;
  sf::Time mGameTime;
};

#endif
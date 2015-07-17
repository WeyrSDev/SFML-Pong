#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "FpsDisplay.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Application
{
public:
  Application();
  void run();
private:
  void handle();
  void update( sf::Time dt );
  void render();

  sf::RenderWindow mWindow;
  sf::RectangleShape mPlayer;
  bool mMoveUp;
  bool mMoveDown;
  FpsDisplay mFpsDisplay;
  sf::Time mTimeStep;
  float mPlayerSpeed;
};

#endif
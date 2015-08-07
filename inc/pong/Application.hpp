#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "FpsDisplay.hpp"
#include "Context.hpp"
#include "GameWorld.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class Application
{
public:
  Application();
  void run();
private:
  void handleEvents();
  void update( sf::Time dt );
  void draw();

  sf::RenderWindow mWindow;
  FpsDisplay mFpsDisplay;
  sf::Time mTimeStep;
  Context mContext;
  GameWorld mWorld;
};

#endif
#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Application
{
public:
  Application();
  void run();
private:
  void handle();
  void update();
  void render();

  sf::RenderWindow mWindow;
  sf::RectangleShape mPlayer;
  bool mMoveUp;
  bool mMoveDown;
};

#endif
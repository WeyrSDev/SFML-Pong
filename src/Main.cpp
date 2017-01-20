#include <game/Application.hpp>

int main()
{
  try {
    Application app;
    app.run();
  } catch( const std::exception& exc ) {
    std::cout << exc.what() << std::endl;
    return -1;
  }
}
#include <game/Application.hpp>
#include <iostream>
#include <stdexcept>

int main()
{
  try {
    Application app;
    app.run();
  } catch( const std::exception& exc ) {
    std::cout << exc.what() << std::endl;
    return EXIT_FAILURE;
  }
}
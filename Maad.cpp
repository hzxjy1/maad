#include "Maad.h"

void Maad::version() {
  std::cout << "Version: " << PROJECT_VERSION_MAJOR << "."
            << PROJECT_VERSION_MINOR << "." << PROJECT_VERSION_PATCH
            << std::endl;
}
#include "Engine.hpp"

#include <iostream>

namespace Engine {

int Engine::Init() {
  gameboard.Init();
  n_line = 0;
  return 0;
}

int Engine::Start() {
  Draw();
  int status = 0;
  while (true) {
    status = Update();
    Draw();
    if (status != 0) {
      break;
    }
  }
  return 0;
}

int Engine::Update() {
  std::string input;
  std::cin >> input;
  n_line += 1;
  if (input[0] == 'q') {
    return 1;
  }
  gameboard.Update(input[0]);
  return 0;
}

int Engine::Draw() {
  n_line += 1;
  n_line = 0;
  while (n_line--) {
    std::cout << "\033[A";
    std::cout << "\033[2K";
  }
  std::cout.flush();
  n_line += gameboard.Draw();
  return 0;
}

int Engine::Terminate() {
  gameboard.Terminate();
  return 0;
}

} /*namespace Engine*/

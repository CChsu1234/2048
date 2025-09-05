#include "Engine.hpp"

#include <iostream>

namespace Engine {

int Engine::Init() {
  gameboard.Init();
  scoreboard.Read();
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
  score = gameboard.getScore();
  scoreboard.AddNewScore(score);
  if (status == 1) {
    std::cout << "YOU LOSE" << std::endl;
  } else if (status == 2) {
    std::cout << "QUIT" << std::endl;
  }
  scoreboard.Draw();
  return 0;
}

int Engine::Update() {
  std::string input;
  std::getline(std::cin, input);
  int result;
  n_line += 1;
  if (input[0] == 'q') {
    return 2;
  }
  result = gameboard.Update(input[0]);
  if (result != 0) {
    return result;
  }
  return 0;
}

int Engine::Draw() {
  while (n_line--) {
    std::cout << "\033[A";
    std::cout << "\033[2K";
  }
  std::cout.flush();
  n_line += gameboard.Draw();
  std::cout << "(w) up (a) left (s) down (d) right (q) quit" << std::endl;
  n_line += 1;
  n_line += 1;
  return 0;
}

int Engine::Terminate() {
  gameboard.Terminate();
  scoreboard.Save();
  return 0;
}

} /*namespace Engine*/

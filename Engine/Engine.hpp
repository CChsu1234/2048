#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <string>

#include "Gameboard.hpp"
#include "Scoreboard.hpp"

namespace Engine {

class Engine {
 private:
  int n_line = 0;;
  void print_on_screen(std::string str);
  int score;
  Gameboard gameboard;
  Scoreboard scoreboard;
 public:
  Engine() = default;
  int Init();
  int Start();
  int Update();
  int Draw();
  int Terminate();
};

} /*namespace Engine*/

#endif

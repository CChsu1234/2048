#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP

#include <set>

namespace Engine {

class Scoreboard {
 private:
  int total;
  std::set<int> scoreboard;
 public:
  Scoreboard() = default;
  int Read();
  int Draw();
  int AddNewScore(int score);
  int Save();
};

} /*namespace Engine*/

#endif

#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP

#include <set>
#include <string>

namespace Engine {

class Scoreboard {
 private:
  int total = -1;
  std::string scoreboard_file;
  std::set<int> scoreboard;
 public:
  Scoreboard() = default;
  int Read();
  int Draw();
  int DrawTitleLine(int current_score);
  int AddNewScore(int score);
  int Save();
};

} /*namespace Engine*/

#endif

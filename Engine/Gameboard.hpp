#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <vector>
#include <map>

namespace Engine {

class Gameboard {
 private:
  int kWidth = 4;
  int kHeight = 4;
  std::vector<std::vector<int>> board;
  std::map<char, int> key_to_dir;

  enum {
    kUp,
    kDown,
    kLeft,
    kRight
  } Direction;

  int dx[4] = {-1, 1, 0, 0};
  int dy[4] = {0, 0, -1, 1};

  int Add();
  int Move(int dir);
  int CanMove(int dir);
  
 public:
  Gameboard() = default;
  int Init();
  int Update(int keycode);
  int Draw();
  int Terminate();
};

} /*namespace Engine*/

#endif

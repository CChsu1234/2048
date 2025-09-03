#include "Gameboard.hpp"

#include <string>
#include <vector>
#include <deque>
#include <utility>
#include <iostream>
#include <iomanip>

#include <time.h>
#include <stdlib.h>

namespace Engine {

int Gameboard::Init() {
  board.resize(kHeight);
  for (int i = 0; i < kHeight; ++i) {
    board[i].resize(kWidth);
  }
  for (int x = 0; x < kHeight; ++x) {
    for (int y = 0; y < kWidth; ++y) {
      board[x][y] = 0;
    }
  }
  key_to_dir.insert({'w', kUp});
  key_to_dir.insert({'s', kDown});
  key_to_dir.insert({'a', kLeft});
  key_to_dir.insert({'d', kRight});
  Add();
  Add();
  return 0;
}

int inRange(int x, int min, int max) {
  return (x >= min && x < max);
}

int Gameboard::CanMove(int dir) {
  for (int i = 0; i < kHeight; ++i) {
    for (int j = 0; j < kWidth; ++j) {
      if (inRange(i + dx[dir], 0, kHeight) 
          && inRange(j + dy[dir], 0, kWidth) 
          && board[i][j] != 0) {
        if (board[i + dx[dir]][j + dy[dir]] == 0 
            || board[i + dx[dir]][j + dy[dir]] == board[i][j]) {
          return 1;
        }
      }
    }
  }
  return 0;
}

int Gameboard::Move(int dir) {
  if (dir == kUp) {
    for (int i = 0; i < kWidth; ++i) {
      std::deque<int> column;
      while (!column.empty()) {
        column.pop_back();
      }
      for (int j = 0; j < kHeight; ++j) {
        if (board[j][i] != 0) {
          if (!column.empty() && board[j][i] == column.back()) {
            column.pop_back();
            column.push_back(board[j][i] * -2);
          } else {
            column.push_back(board[j][i]);
          }
          board[j][i] = 0;
        }
      }
      for (int j = 0; j < kHeight; ++j) {
        if (column.empty()) {
          break;
        }
        board[j][i] = abs(column.front());
        column.pop_front();
      }
    }
  } else if (dir == kDown) {
    for (int i = 0; i < kWidth; ++i) {
      std::deque<int> column;
      while (!column.empty()) {
        column.pop_back();
      }
      for (int j = kHeight - 1; j >= 0; --j) {
        if (board[j][i] != 0) {
          if (!column.empty() && board[j][i] == column.back()) {
            column.pop_back();
            column.push_back(board[j][i] * -2);
          } else {
            column.push_back(board[j][i]);
          }
          board[j][i] = 0;
        }
      }
      for (int j = kHeight - 1; j >= 0; --j) {
        if (column.empty()) {
          break;
        }
        board[j][i] = abs(column.front());
        column.pop_front();
      }
    }
  } else if (dir == kLeft) {
    for (int i = 0; i < kHeight; ++i) {
      std::deque<int> column;
      while (!column.empty()) {
        column.pop_back();
      }
      for (int j = 0; j < kWidth; ++j) {
        if (board[i][j] != 0) {
          if (!column.empty() && board[i][j] == column.back()) {
            column.pop_back();
            column.push_back(board[i][j] * -2);
          } else {
            column.push_back(board[i][j]);
          }
          board[i][j] = 0;
        }
      }
      for (int j = 0; j < kWidth; ++j) {
        if (column.empty()) {
          break;
        }
        board[i][j] = abs(column.front());
        column.pop_front();
      }
    }
  } else if (dir == kRight) {
    for (int i = 0; i < kHeight; ++i) {
      std::deque<int> column;
      while (!column.empty()) {
        column.pop_back();
      }
      for (int j = kWidth - 1; j >= 0; --j) {
        if (board[i][j] != 0) {
          if (!column.empty() && board[i][j] == column.back()) {
            column.pop_back();
            column.push_back(board[i][j] * -2);
          } else {
            column.push_back(board[i][j]);
          }
          board[i][j] = 0;
        }
      }
      for (int j = kWidth - 1; j >= 0; --j) {
        if (column.empty()) {
          break;
        }
        board[i][j] = abs(column.front());
        column.pop_front();
      }
    }
  }
  return 0;
}

int Gameboard::Add() {
  srand( time(NULL) );
  std::vector<std::pair<int, int>> free_space;
  for (int i = 0; i < kHeight; ++i) {
    for (int j = 0; j < kWidth; ++j) {
      if (board[i][j] == 0) {
        free_space.push_back({i, j});
      }
    }
  }
  int n = rand() % free_space.size();
  std::pair<int, int> target = free_space[n];
  board[target.first][target.second] = 2;
  return 0;
}

int Gameboard::Update(int keycode) {
  int dir;
  auto key_to_dir_pair = key_to_dir.find(keycode);
  if (key_to_dir_pair != key_to_dir.end()) {
    dir = key_to_dir_pair->second;
    if (CanMove(dir)) {
      Move(dir);
      Add();
    }
  }
  for (int i = 0; i < 4; ++i) {
    if (!CanMove(i)) {
      return 1;
    }
  }
  return 0;
}

int Gameboard::Draw() {
  for (int i = 0; i < 1 + 5 * kWidth; ++i) {
    std::cout << '#';
  }
  std::cout << std::endl;
  for (int x = 0; x < kHeight; ++x) {
    std::cout << '#';
    for (int y = 0; y < kWidth; ++y) {
      std::cout 
        << std::setw(4) 
        << ((board[x][y] == 0 ) ? "." : std::to_string(board[x][y])) 
        << ((y == kWidth - 1) ? "#\n" : " ");
    }
  }
  for (int i = 0; i < 1 + 5 * kWidth; ++i) {
    std::cout << '#';
  }
  std::cout << std::endl;
  return kHeight + 2;
}

int Gameboard::Terminate() {
  return 0;
}

} /*namespace Engine*/

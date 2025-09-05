#include "Gameboard.hpp"

#include <string>
#include <vector>
#include <deque>
#include <utility>
#include <iostream>

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

namespace Engine {

int Gameboard::Init() {
  kHeight = 4;
  kWidth = 4;
  score = 0;
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
  number_to_color.insert({2, "#EEE4DA"});
  number_to_color.insert({4, "#ECE0C8"});
  number_to_color.insert({8, "#F2B179"});
  number_to_color.insert({16, "#F59565"});
  number_to_color.insert({32, "#F77B5F"});
  number_to_color.insert({64, "#F35F3B"});
  number_to_color.insert({128, "#EDCE71"});
  number_to_color.insert({256, "#EDCC61"});
  number_to_color.insert({512, "#ECC850"});
  number_to_color.insert({1024, "#EDC53F"});
  number_to_color.insert({2048, "#E9B501"});
  number_to_color.insert({4096, "#FCEDD8"});
  Add();
  Add();
  return 0;
}

static int inRange(int x, int min, int max) {
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
            score += board[j][i] * 2;
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
            score += board[j][i] * 2;
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
            score += board[i][j] * 2;
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
            score += board[i][j] * 2;
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
  board[target.first][target.second] = 2 * ((1 + (rand() % 10 + 1) / 10));
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
    if (CanMove(i)) {
      return 0;
    }
  }
  return 1;
}

static void print_html_color_text(std::string output_string, std::string html_color) {
  std::string hexcolor = html_color.substr(1);

  std::string hexR = hexcolor.substr(0, 2);
  std::string hexG = hexcolor.substr(2, 2);
  std::string hexB = hexcolor.substr(4, 2);

  int R = std::stoi(hexR, nullptr, 16);
  int G = std::stoi(hexG, nullptr, 16);
  int B = std::stoi(hexB, nullptr, 16);

  printf("\x1b[38;2;%d;%d;%dm%s\x1b[0m", R, G, B, output_string.c_str());
}

void Gameboard::DrawColorText(int n) {
  auto target = number_to_color.find(n);
  int length = std::to_string(n).length();
  for (int i = 4; i > length; --i) {
    std::cout << ' ';
  }
  if (n == 0) {
    std::cout << '.';
  } else if (target == number_to_color.end()) {
    print_html_color_text(std::to_string(n), "#FBEFE3");
  } else {
    auto color = target->second;
    print_html_color_text(std::to_string(n), color);
  }
}

int Gameboard::Draw() {
  for (int i = 0; i < 2 + 5 * kWidth; ++i) {
    std::cout << '#';
  }
  std::cout << std::endl;
  for (int x = 0; x < kHeight; ++x) {
    std::cout << '#';
    for (int y = 0; y < kWidth; ++y) {
      DrawColorText(board[x][y]);
      std::cout << ' ';
    }
    std::cout << "#\n";
  }
  for (int i = 0; i < 2 + 5 * kWidth; ++i) {
    std::cout << '#';
  }
  std::cout << std::endl;
  std::cout << "score: " << score << std::endl;
  return kHeight + 3;
}

int Gameboard::Terminate() {
  return 0;
}

int Gameboard::getScore() {
  return score;
}

} /*namespace Engine*/

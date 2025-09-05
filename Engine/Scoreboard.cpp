#include "Scoreboard.hpp"

#include <iostream>
#include <fstream>
#include <set>

namespace Engine {

int Scoreboard::Read() {
  scoreboard.clear();
  std::ifstream in_file;
  in_file.open("./Resource/Scoreboard.txt");
  in_file >> total;
  if (in_file.fail()) {
    total = 0;
    return 0;
  }
  int score;
  for (int i = 0; i < total; ++i) {
    in_file >> score;
    scoreboard.insert(score);
  }
  in_file.close();
  return 0;
}

int Scoreboard::DrawTitleLine(int current_score) {
  int prev_best_score = *(scoreboard.rbegin());
  std::cout 
    << "Best: "
    << ((current_score > prev_best_score) ? current_score : prev_best_score)
    << ", Current: "
    << current_score
    << std::endl;
  return 1;
}

int Scoreboard::Draw() {
  std::cout << "SCORE BOARD" << std::endl;
  int rank = 0;
  for (auto score = scoreboard.rbegin(); score != scoreboard.rend(); ++score) {
    std::cout << ++rank << ". " << *score << std::endl;
    if (rank >= 10) {
      break;
    }
  }
  return 0;
}

int Scoreboard::AddNewScore(int score) {
  if (score) {
    scoreboard.insert(score);
    ++total;
  }
  return 0;
}

int Scoreboard::Save() {
  std::ofstream out_file;
  out_file.open("./Resource/Scoreboard.txt");
  out_file << total << '\n';
  for (auto score = scoreboard.begin(); score != scoreboard.end(); ++score) {
    out_file << *score << '\n';
  }
  out_file.close();
  return 0;
}

} /*namespace Engine*/

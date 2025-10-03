#include "Engine.hpp"

#include <iostream>

#include <sys/stat.h>
#include <stdlib.h>
#include <pthread.h> // Multithreading
#include <stdio.h>
#include <stdlib.h>  // for atexit()
#include <termios.h> // For changing terminal mode
#include <unistd.h>  // For changing terminal mode

#include "Gameboard.hpp"
#include "Scoreboard.hpp"

namespace Engine {

void disableRAWMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH,
            &original); // Set terminal to original state
}

/// This function enables RAW mode for terminal.
void enableRAWMode() {
  struct termios raw;
  tcgetattr(STDIN_FILENO, &raw); // Save the state of the terminal to struct raw
                                 // STDIN_FILENO is from <stdlib.h>
                                 // tcgetattr() from <termios.h>
  tcgetattr(STDIN_FILENO, &original);
  atexit(&disableRAWMode); // Revert to canonical mode when exiting the program
                           // atext() from <stdlib.h>
  raw.c_lflag &=
      ~(ECHO | ICANON); // Turn off canonical mode
                        // Turn off ECHO mode so that keyboard is not
                        // printing to terminal
                        // ICANON and ECHO is bitflag. ~ is binary NOT operator

  tcsetattr(STDIN_FILENO, TCSAFLUSH,
            &raw); // Set the terminal to be in raw mode
                   // tcsetattr() from <termios.h>
}

int Engine::Init() {
  gameboard.Init();
  scoreboard.Read();
  n_line = 0;

#ifndef GAME_ROOT
  fprintf(stderr, "GAME_ROOT not define\n");
  std::exit(1);
#endif

#ifdef GAME_ROOT
  struct stat info;
  if (stat(GAME_ROOT, &info) || !(info.st_mode & S_IFDIR)) {
    std::cerr << "GAME_ROOT \'" << GAME_ROOT << "\' not exit)" << std::endl;
    std::exit(1);
  }
#endif

  enableRAWMode();

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
    printf("YOU LOSE\n");
  } else if (status == 2) {
    printf("QUIT\n");
  }
  scoreboard.Draw();
  return 0;
}

int Engine::Update() {
  char input;
  input = getchar();
  int result;
  if (input == 'q') {
    return 2;
  }
  result = gameboard.Update(input);
  if (result != 0) {
    return result;
  }
  return 0;
}

int Engine::Draw() {
  while (n_line--) {
    printf("\033[A\033[2K");
  }
  n_line += scoreboard.DrawTitleLine(gameboard.getScore());
  n_line += gameboard.Draw();
  printf("(w) up (a) left (s) down (d) right (q) quit\n");
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

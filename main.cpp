#include "Engine/Engine.hpp"

int main() {
  Engine::Engine engine;
  engine.Init();
  engine.Start();
  engine.Terminate();
  return 0;
}

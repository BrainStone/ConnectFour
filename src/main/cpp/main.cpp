#include "main.hpp"

#include <windows.h>

#include <random>

#include "console.hpp"
#include "game.hpp"

int main() {
  setupGame();

  std::default_random_engine generator(0);
  std::uniform_int_distribution<int16_t> columDist(0, gridWidth - 1);
  std::uniform_int_distribution<int16_t> rowDist(-1, gridHeight - 1);
  std::bernoulli_distribution colorDist(0.5);

  for (int i = 0; i < 100; ++i) {
    drawStone(position(columDist(generator), rowDist(generator)), colorDist(generator));

    Sleep(100);
  }

  return EXIT_SUCCESS;
}

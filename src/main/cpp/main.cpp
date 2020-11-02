#include "main.hpp"

#include <windows.h>

#include <random>

#include "game.hpp"

int main() {
  setupGame();

  std::default_random_engine generator(0);
  std::uniform_int_distribution<int16_t> columDist(0, gridWidth - 1);
  std::bernoulli_distribution colorDist(0.5);

  boardState state;

  for (int i = 0; i < 100; ++i) {
    state = state.dropPiece(columDist(generator), colorDist(generator) ? boardPiece::RED : boardPiece::YELLOW).value_or(state);
    state.render();

    Sleep(100);
  }

  return EXIT_SUCCESS;
}

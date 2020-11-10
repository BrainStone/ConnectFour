#include "main.hpp"

#include <random>

#include <windows.h>

#include "game.hpp"

int main() {
  setupGame();

  std::default_random_engine generator(0);
  std::uniform_int_distribution<int16_t> columDist(0, gridWidth - 1);
  std::bernoulli_distribution colorDist(0.5);

  boardState state;

  for (int i = 0; i < 100; ++i) {
    state = state.dropPiece(columDist(generator), colorDist(generator) ? boardPiece::RED : boardPiece::YELLOW).value_or(state);
    state.render(false);

    Sleep(100);

    state.render();
    if (state.getWinner()) break;
  }

  Sleep(100);

  for (int16_t column = 0; column < gridWidth; ++column) {
    boardPiece piece = colorDist(generator) ? boardPiece::RED : boardPiece::YELLOW;

    drawStone({column, -1}, piece);
    drawStone({column, state.getColumnFreeRow(column)}, piece, false);

    Sleep(500);
  }

  return EXIT_SUCCESS;
}

#include "game.hpp"

#include <iostream>

position size;
position startPos;

boardState::boardState() : board() {}
boardState::boardState(const boardState& copy) : board(copy.board) {}

boardPiece boardState::getAtPosition(const position& pos) {
  const size_t baseOffset = getBaseOffset(pos);

  if (board.test(baseOffset))
    return boardPiece::RED;
  else if (board.test(baseOffset + 1))
    return boardPiece::YELLOW;
  else
    return boardPiece::EMPTY;
}

void boardState::setAtPosition(const position& pos, const boardPiece& piece) {
  const size_t baseOffset = getBaseOffset(pos);

  board.set(baseOffset, piece == boardPiece::RED);
  board.set(baseOffset + 1, piece == boardPiece::YELLOW);
}

void setupGame() {
  setupConsole();

  size = getConsoleSize();
  startPos = ((size - 1) - renderGridSize) / 2;

  drawGrid();
}

void drawGrid() {
  moveCursor(startPos);
  printAnsiSequence("90m");

  uint16_t x, y;
  for (y = 0; y < renderGridHeight; ++y) {
    if (y != 0) moveCursor(startPos + position(0, y));

    const bool connectLeftRight = (y % 2) == 0;

    for (x = 0; x < renderGridWidth; ++x) {
      const bool connectUpDown = (x % 2) == 0;

      std::cout << getBoxChar(connectUpDown && (y > 0), connectLeftRight && (x < (renderGridWidth - 1)), connectUpDown && (y < (renderGridHeight - 1)),
                              connectLeftRight && (x > 0));
    }
  }

  std::cout.flush();
}

void drawStone(const position& pos, bool color) {
  moveCursor(startPos + ((pos * 2) + position(1, 1)));

  if (color)
    printAnsiSequence("91m");
  else
    printAnsiSequence("93m");

  std::cout << 'O' << std::flush;
}

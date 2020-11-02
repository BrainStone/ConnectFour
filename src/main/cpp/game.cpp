#include "game.hpp"

#include <iostream>

position size;
position startPos;

boardState::boardState() : board() {}
boardState::boardState(const boardState& copy) : board(copy.board) {}

void boardState::render() const {
  position pos(0, 0);

  for (pos.column = 0; pos.column < gridWidth; ++pos.column) {
    for (pos.row = 0; pos.row < gridHeight; ++pos.row) {
      drawStone(pos, getAtPosition(pos), false);
    }
  }

  std::cout.flush();
}

std::optional<boardState> boardState::dropPiece(int16_t column, const boardPiece& piece) const {
  if (piece == boardPiece::EMPTY) return std::nullopt;

  position pos(column, gridHeight - 1);

  for (; pos.row >= 0; --pos.row) {
    if (getAtPosition(pos) == boardPiece::EMPTY) {
      boardState copy(*this);

      copy.setAtPosition(pos, piece);

      return copy;
    }
  }

  return std::nullopt;
}

boardPiece boardState::getAtPosition(const position& pos) const {
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

void drawStone(const position& pos, const boardPiece& piece, bool flush) {
  moveCursor(startPos + ((pos * 2) + position(1, 1)));

  if (piece == boardPiece::EMPTY) {
    std::cout << ' ';
  } else {
    if (piece == boardPiece::RED)
      printAnsiSequence("91m");
    else
      printAnsiSequence("93m");

    std::cout << 'O';
  }

  if (flush) std::cout.flush();
}

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
      drawStone(pos, getAtPosition(pos), true, false);
    }
  }

  std::cout.flush();
}

int16_t boardState::getColumnFreeRow(int16_t column) const {
  position pos(column, gridHeight - 1);

  for (; pos.row >= 0; --pos.row) {
    if (getAtPosition(pos) == boardPiece::EMPTY) {
      return pos.row;
    }
  }

  return -1;
}

std::optional<boardState> boardState::dropPiece(int16_t column, const boardPiece& piece) const {
  if (piece == boardPiece::EMPTY) return std::nullopt;

  int16_t freeRow = getColumnFreeRow(column);

  if (freeRow < 0) return std::nullopt;

  boardState copy(*this);

  copy.setAtPosition({column, freeRow}, piece);

  return copy;
}

std::optional<boardPiece> boardState::getWinner() const {
  constexpr position offsetX(1, 0);
  constexpr position offsetY(0, 1);
  constexpr position offsetDigDown(1, 1);
  constexpr position offsetDigUp(1, -1);

  position pos;
  boardPiece basePiece;

  // Left - Right
  for (pos = {0, 0}; pos.column < (gridWidth - 3); ++pos.column) {
    for (pos.row = 0; pos.row < gridHeight; ++pos.row) {
      basePiece = getAtPosition(pos);

      if ((basePiece != boardPiece::EMPTY) && (basePiece == getAtPosition(pos + (offsetX * 1))) && (basePiece == getAtPosition(pos + (offsetX * 2))) &&
          (basePiece == getAtPosition(pos + (offsetX * 3))))
        return basePiece;
    }
  }

  // Top - Down
  for (pos = {0, 0}; pos.column < gridWidth; ++pos.column) {
    for (pos.row = 0; pos.row < (gridHeight - 3); ++pos.row) {
      basePiece = getAtPosition(pos);

      if ((basePiece != boardPiece::EMPTY) && (basePiece == getAtPosition(pos + (offsetY * 1))) && (basePiece == getAtPosition(pos + (offsetY * 2))) &&
          (basePiece == getAtPosition(pos + (offsetY * 3))))
        return basePiece;
    }
  }

  // If no winner was found, let's check if the board is full
  // If there's any space at the top of the board there's still room
  for (pos = {0, 0}; pos.column < gridWidth; ++pos.column) {
    if (getAtPosition(pos) == boardPiece::EMPTY) return std::nullopt;
  }

  // Draw
  return boardPiece::EMPTY;
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

bool boardState::operator==(const boardState& rhs) const { return board == rhs.board; }

bool boardState::operator!=(const boardState& rhs) const { return board != rhs.board; }

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

void drawStone(const position& pos, const boardPiece& piece, bool fullColor, bool flush) {
  moveCursor(startPos + ((pos * 2) + position(1, 1)));

  if (piece == boardPiece::EMPTY) {
    std::cout << ' ';
  } else {
    if (piece == boardPiece::RED)
      printAnsiSequence(fullColor ? "91m" : "31m");
    else
      printAnsiSequence(fullColor ? "93m" : "33m");

    std::cout << 'O';
  }

  if (flush) std::cout.flush();
}

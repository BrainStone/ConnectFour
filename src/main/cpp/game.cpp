#include "game.hpp"

#include <iostream>

position size;
position startPos;

boardState::boardState() : board(), winParams(std::nullopt), winParamsCalculated(false) {}
boardState::boardState(const boardState& copy) : board(copy.board), winParams(copy.winParams), winParamsCalculated(copy.winParamsCalculated) {}

void boardState::render(bool showWin) const {
  const std::optional<winningParameters>& wP = getWinningParameters();
  const bool winnerFound = showWin && (wP && (std::get<0>(*wP) != boardPiece::EMPTY));
  position pos(0, 0);

  for (pos.column = 0; pos.column < gridWidth; ++pos.column) {
    for (pos.row = 0; pos.row < gridHeight; ++pos.row) {
      drawStone(pos, getAtPosition(pos), !winnerFound, false);
    }
  }

  if (winnerFound) {
    const position startPos = std::get<1>(*wP);
    const position offset = std::get<2>(*wP);
    const position pastEndPos = startPos + (offset * 4);

    for (pos = startPos; pos != pastEndPos; pos += offset) {
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
  const std::optional<winningParameters>& wP = getWinningParameters();

  if (wP)
    return std::get<0>(*wP);
  else
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
  winParamsCalculated = false;

  const size_t baseOffset = getBaseOffset(pos);

  board.set(baseOffset, piece == boardPiece::RED);
  board.set(baseOffset + 1, piece == boardPiece::YELLOW);
}

const std::optional<winningParameters>& boardState::getWinningParameters() const {
  if (!winParamsCalculated) {
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
            (basePiece == getAtPosition(pos + (offsetX * 3)))) {
          winParams.emplace(basePiece, pos, offsetX);
          winParamsCalculated = true;

          return winParams;
        }
      }
    }

    // Top - Down
    for (pos = {0, 0}; pos.column < gridWidth; ++pos.column) {
      for (pos.row = 0; pos.row < (gridHeight - 3); ++pos.row) {
        basePiece = getAtPosition(pos);

        if ((basePiece != boardPiece::EMPTY) && (basePiece == getAtPosition(pos + (offsetY * 1))) && (basePiece == getAtPosition(pos + (offsetY * 2))) &&
            (basePiece == getAtPosition(pos + (offsetY * 3)))) {
          winParams.emplace(basePiece, pos, offsetY);
          winParamsCalculated = true;

          return winParams;
        }
      }
    }

    // Diagonal Top Left - Bottom Right
    for (pos = {0, 0}; pos.column < (gridWidth - 3); ++pos.column) {
      for (pos.row = 0; pos.row < (gridHeight - 3); ++pos.row) {
        basePiece = getAtPosition(pos);

        if ((basePiece != boardPiece::EMPTY) && (basePiece == getAtPosition(pos + (offsetDigDown * 1))) &&
            (basePiece == getAtPosition(pos + (offsetDigDown * 2))) && (basePiece == getAtPosition(pos + (offsetDigDown * 3)))) {
          winParams.emplace(basePiece, pos, offsetDigDown);
          winParamsCalculated = true;

          return winParams;
        }
      }
    }

    // Diagonal Bottom Left - Top Right
    for (pos = {0, 0}; pos.column < (gridWidth - 3); ++pos.column) {
      for (pos.row = gridHeight - 1; pos.row >= 3; --pos.row) {
        basePiece = getAtPosition(pos);

        if ((basePiece != boardPiece::EMPTY) && (basePiece == getAtPosition(pos + (offsetDigUp * 1))) &&
            (basePiece == getAtPosition(pos + (offsetDigUp * 2))) && (basePiece == getAtPosition(pos + (offsetDigUp * 3)))) {
          winParams.emplace(basePiece, pos, offsetDigUp);
          winParamsCalculated = true;

          return winParams;
        }
      }
    }

    // If no winner was found, let's check if the board is full
    // If there's any space at the top of the board there's still room
    for (pos = {0, 0}; pos.column < gridWidth; ++pos.column) {
      if (getAtPosition(pos) == boardPiece::EMPTY) {
        winParams = std::nullopt;
        winParamsCalculated = true;

        return winParams;
      }
    }

    // Draw
    winParams.emplace(boardPiece::EMPTY, position(), position());
    winParamsCalculated = true;
  }

  return winParams;
}

boardState& boardState::operator=(const boardState& copy) {
  board = copy.board;
  winParamsCalculated = copy.winParamsCalculated;

  if (copy.winParams)
    winParams.emplace(copy.winParams.value());
  else
    winParams = std::nullopt;

  return *this;
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

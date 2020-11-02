#pragma once

#include <bitset>
#include <optional>

#include "console.hpp"

constexpr int16_t gridWidth = 7;
constexpr int16_t gridHeight = 6;

constexpr int16_t renderGridWidth = gridWidth * 2 + 1;
constexpr int16_t renderGridHeight = gridHeight * 2 + 1;

// Helper
constexpr position renderGridSize(renderGridWidth, renderGridHeight);

extern position size;
extern position startPos;

enum class boardPiece { EMPTY = 0b00, RED = 0b01, YELLOW = 0b10 };

class boardState {
 private:
  std::bitset<gridWidth * gridHeight * 2> board;

  static constexpr size_t getBaseOffset(const position& pos) { return (pos.column + (pos.row * gridWidth)) * 2; }

 public:
  boardState();
  boardState(const boardState& copy);

  void render() const;
  std::optional<boardState> dropPiece(int16_t column, const boardPiece& piece) const;

  // Low level methods. Avoid if possible!
  boardPiece getAtPosition(const position& pos) const;
  void setAtPosition(const position& pos, const boardPiece& piece);

  constexpr bool operator==(const boardState& rhs) const { return board == rhs.board; }
  constexpr bool operator!=(const boardState& rhs) const { return board != rhs.board; };
};

void setupGame();

void drawGrid();
void drawStone(const position& pos, const boardPiece& piece, bool flush = true);

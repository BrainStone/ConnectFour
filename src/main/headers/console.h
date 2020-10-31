#pragma once

#include <cstdint>
#include <string>

struct consolePosition {
  int16_t column;
  int16_t row;

  constexpr consolePosition() : column(0), row(0){};
  constexpr consolePosition(int16_t column, int16_t row) : column(column), row(row){};
  constexpr consolePosition(const consolePosition& copy) = default;
  constexpr consolePosition(consolePosition&& move) = default;

  consolePosition& operator=(const consolePosition& rhs) = default;

  constexpr consolePosition operator+(const consolePosition& rhs) const { return consolePosition(column + rhs.column, row + rhs.row); }
  constexpr consolePosition operator-(const consolePosition& rhs) const { return consolePosition(column - rhs.column, row - rhs.row); }

  constexpr consolePosition operator*(int16_t rhs) const { return consolePosition(column * rhs, row * rhs); }
  constexpr consolePosition operator/(int16_t rhs) const { return consolePosition(column / rhs, row / rhs); }
};

void setupConsole();
void enableColorCodes();
void resetConsole();

consolePosition getConsoleSize();

void printAnsiSequence(const std::string& sequence, bool includeBracket = true);
void clearScreen();
void hideCursor();
void moveCursor(const consolePosition& pos);
void moveCursor(uint16_t column, uint16_t row);

std::string getBoxChar(bool up, bool right, bool down, bool left);

#pragma once

#include <cstdint>
#include <string>

struct position {
  int16_t column;
  int16_t row;

  constexpr position() : column(0), row(0){};
  constexpr position(int16_t column, int16_t row) : column(column), row(row){};
  constexpr position(const position& copy) = default;
  constexpr position(position&& move) = default;

  position& operator=(const position& rhs) = default;

  constexpr position operator+(const position& rhs) const { return position(column + rhs.column, row + rhs.row); }
  constexpr position operator-(const position& rhs) const { return position(column - rhs.column, row - rhs.row); }

  constexpr position operator+(int16_t rhs) const { return position(column + rhs, row + rhs); }
  constexpr position operator-(int16_t rhs) const { return position(column - rhs, row - rhs); }
  constexpr position operator*(int16_t rhs) const { return position(column * rhs, row * rhs); }
  constexpr position operator/(int16_t rhs) const { return position(column / rhs, row / rhs); }

  constexpr position operator+=(const position& rhs) {
    column += rhs.column;
    row += rhs.row;

    return *this;
  }

  constexpr position operator-=(const position& rhs) {
    column -= rhs.column;
    row -= rhs.row;

    return *this;
  }

  constexpr position operator+=(int16_t rhs) {
    column += rhs;
    row += rhs;

    return *this;
  }

  constexpr position operator-=(int16_t rhs) {
    column -= rhs;
    row -= rhs;

    return *this;
  }

  constexpr position operator*=(int16_t rhs) {
    column *= rhs;
    row *= rhs;

    return *this;
  }

  constexpr position operator/=(int16_t rhs) {
    column /= rhs;
    row /= rhs;

    return *this;
  }

  constexpr bool operator==(const position& rhs) const { return (column == rhs.column) && (row == rhs.row); }
  constexpr bool operator!=(const position& rhs) const { return !(*this == rhs); }
};

void setupConsole();
void enableColorCodes();
void resetConsole();

position getConsoleSize();

void printAnsiSequence(const std::string& sequence, bool includeBracket = true);
void clearScreen();
void hideCursor();
void moveCursor(const position& pos);
void moveCursor(uint16_t column, uint16_t row);

std::string getBoxChar(bool up, bool right, bool down, bool left);

#include "console.h"

#include <windows.h>

#include <cstdlib>
#include <iostream>
#include <sstream>

void setupConsole() {
  enableColorCodes();
  clearScreen();
  hideCursor();
  std::atexit(resetConsole);
}

void enableColorCodes() {
  try {
    // UTF-8
    SetConsoleOutputCP(65001);

    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdout == INVALID_HANDLE_VALUE) throw "GetStdHandle";

    DWORD dwMode = 0;
    if (!GetConsoleMode(hStdout, &dwMode)) throw "GetConsoleMode";

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hStdout, dwMode)) throw "SetConsoleMode";
  } catch (const char* e) {
    std::cerr << e << std::endl;
    std::exit(1);
  }
}

void resetConsole() {
  Sleep(10000);
  printAnsiSequence("c", false);
}

consolePosition getConsoleSize() {
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

  return consolePosition(csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
}

void printAnsiSequence(const std::string& sequence, bool includeBracket) {
  std::cout << '\033';
  if (includeBracket) std::cout << '[';

  std::cout << sequence;
}

void clearScreen() {
  printAnsiSequence("2J");
  moveCursor(0, 0);
}

void hideCursor() { printAnsiSequence("?25l"); }

void moveCursor(const consolePosition& pos) { moveCursor(pos.column, pos.row); }

void moveCursor(uint16_t column, uint16_t row) {
  std::ostringstream ss;

  ss << row << ';' << column << 'H';

  printAnsiSequence(ss.str());
}

std::string getBoxChar(bool up, bool right, bool down, bool left) {
  uint8_t val = (up << 3) | (right << 2) | (down << 1) | (left << 0);

  switch (val) {
    default:
    case 0b0000:
      return " ";
    case 0b0001:
    case 0b0100:
    case 0b0101:
      return "═";
    case 0b0010:
    case 0b1000:
    case 0b1010:
      return "║";
    case 0b0011:
      return "╗";
    case 0b0110:
      return "╔";
    case 0b0111:
      return "╦";
    case 0b1001:
      return "╝";
    case 0b1011:
      return "╣";
    case 0b1100:
      return "╚";
    case 0b1101:
      return "╩";
    case 0b1110:
      return "╠";
    case 0b1111:
      return "╬";
  }
}

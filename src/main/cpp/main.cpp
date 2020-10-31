#include "main.h"

#include <windows.h>

#include <iostream>
#include <random>

constexpr uint16_t gridWidth = 7;
constexpr uint16_t gridHeight = 6;

constexpr uint16_t renderGridWidth = gridWidth * 2 + 1;
constexpr uint16_t renderGridHeight = gridHeight * 2 + 1;

// Helper
constexpr consolePosition renderGridSize(renderGridWidth, renderGridHeight);

consolePosition size;
consolePosition startPos;

int main() {
  setupConsole();

  size = getConsoleSize();
  startPos = (size - renderGridSize) / 2;

  drawGrid();

  std::default_random_engine generator(0);
  std::uniform_int_distribution<int16_t> columDist(0, gridWidth - 1);
  std::uniform_int_distribution<int16_t> rowDist(-1, gridHeight - 1);
  std::bernoulli_distribution colorDist(0.5);

  for (int i = 0; i < 20; ++i) {
    drawStone(consolePosition(columDist(generator), rowDist(generator)), colorDist(generator));

    Sleep(500);
  }

  return EXIT_SUCCESS;
}

void drawGrid() {
  moveCursor(startPos);
  printAnsiSequence("90m");

  uint16_t x, y;
  for (y = 0; y < renderGridHeight; ++y) {
    if (y != 0) moveCursor(startPos + consolePosition(0, y));

    const bool connectLeftRight = (y % 2) == 0;

    for (x = 0; x < renderGridWidth; ++x) {
      const bool connectUpDown = (x % 2) == 0;

      std::cout << getBoxChar(connectUpDown && (y > 0), connectLeftRight && (x < (renderGridWidth - 1)), connectUpDown && (y < (renderGridHeight - 1)),
                              connectLeftRight && (x > 0));
    }
  }

  std::cout.flush();
}

void drawStone(consolePosition pos, bool color) {
  moveCursor(startPos + ((pos * 2) + consolePosition(1, 1)));

  if (color)
    printAnsiSequence("91m");
  else
    printAnsiSequence("93m");

  std::cout << 'O' << std::flush;
}

#include "test.hpp"

#include <cassert>
#include <utility>

#include "game.hpp"

int main() {
  rightLeft();
  topDown();
  diagDown();
  diagUp();
  draw();

  return EXIT_SUCCESS;
}

void heightLimit() {
  try {
    // Check height limit (ok)
    assert(boardState()
               .dropPiece(0, boardPiece::RED)
               .value()
               .dropPiece(0, boardPiece::YELLOW)
               .value()
               .dropPiece(0, boardPiece::RED)
               .value()
               .dropPiece(0, boardPiece::YELLOW)
               .value()
               .dropPiece(0, boardPiece::RED)
               .value()
               .dropPiece(0, boardPiece::YELLOW));
    // Check height limit (not ok)
    assert(!boardState()
                .dropPiece(0, boardPiece::RED)
                .value()
                .dropPiece(0, boardPiece::YELLOW)
                .value()
                .dropPiece(0, boardPiece::RED)
                .value()
                .dropPiece(0, boardPiece::YELLOW)
                .value()
                .dropPiece(0, boardPiece::RED)
                .value()
                .dropPiece(0, boardPiece::YELLOW)
                .value()
                .dropPiece(0, boardPiece::RED));
  } catch (const std::bad_optional_access& e) {
    assert(false);
  }
}

void rightLeft() {
  try {
    // 3 Red pieces next to eachother
    assert(!boardState().dropPiece(0, boardPiece::RED).value().dropPiece(1, boardPiece::RED).value().dropPiece(2, boardPiece::RED).value().getWinner());
    // 4 Red pieces next to eachother
    assert(boardState()
               .dropPiece(0, boardPiece::RED)
               .value()
               .dropPiece(1, boardPiece::RED)
               .value()
               .dropPiece(2, boardPiece::RED)
               .value()
               .dropPiece(3, boardPiece::RED)
               .value()
               .getWinner());
    // Almost 4 Red pieces next to eachother with one yellow
    assert(!boardState()
                .dropPiece(0, boardPiece::RED)
                .value()
                .dropPiece(1, boardPiece::RED)
                .value()
                .dropPiece(2, boardPiece::YELLOW)
                .value()
                .dropPiece(3, boardPiece::RED)
                .value()
                .dropPiece(4, boardPiece::RED)
                .value()
                .getWinner());
  } catch (const std::bad_optional_access& e) {
    assert(false);
  }
}

void topDown() {
  try {
    // 3 Red pieces on top of eachother
    assert(!boardState().dropPiece(0, boardPiece::RED).value().dropPiece(0, boardPiece::RED).value().dropPiece(0, boardPiece::RED).value().getWinner());
    // 4 Red pieces on top of eachother
    assert(boardState()
               .dropPiece(0, boardPiece::RED)
               .value()
               .dropPiece(0, boardPiece::RED)
               .value()
               .dropPiece(0, boardPiece::RED)
               .value()
               .dropPiece(0, boardPiece::RED)
               .value()
               .getWinner());
    // Almost 4 Red pieces on top of eachother with one yellow
    assert(!boardState()
                .dropPiece(0, boardPiece::RED)
                .value()
                .dropPiece(0, boardPiece::RED)
                .value()
                .dropPiece(0, boardPiece::YELLOW)
                .value()
                .dropPiece(0, boardPiece::RED)
                .value()
                .dropPiece(0, boardPiece::RED)
                .value()
                .getWinner());
  } catch (const std::bad_optional_access& e) {
    assert(false);
  }
}

void diagDown() {
  try {
    // Yellow 3 pyramid with incomplete red diagonal on top
    assert(!boardState()
                .dropPiece(0, boardPiece::YELLOW)
                .value()
                .dropPiece(0, boardPiece::YELLOW)
                .value()
                .dropPiece(0, boardPiece::YELLOW)
                .value()
                .dropPiece(1, boardPiece::YELLOW)
                .value()
                .dropPiece(1, boardPiece::YELLOW)
                .value()
                .dropPiece(2, boardPiece::YELLOW)
                .value()
                .dropPiece(0, boardPiece::RED)
                .value()
                .dropPiece(1, boardPiece::RED)
                .value()
                .dropPiece(2, boardPiece::RED)
                .value()
                .getWinner());
    // Yellow 3 pyramid with red diagonal on top
    assert(boardState()
               .dropPiece(0, boardPiece::YELLOW)
               .value()
               .dropPiece(0, boardPiece::YELLOW)
               .value()
               .dropPiece(0, boardPiece::YELLOW)
               .value()
               .dropPiece(1, boardPiece::YELLOW)
               .value()
               .dropPiece(1, boardPiece::YELLOW)
               .value()
               .dropPiece(2, boardPiece::YELLOW)
               .value()
               .dropPiece(0, boardPiece::RED)
               .value()
               .dropPiece(1, boardPiece::RED)
               .value()
               .dropPiece(2, boardPiece::RED)
               .value()
               .dropPiece(3, boardPiece::RED)
               .value()
               .getWinner());
    // Yellow 3 pyramid with almost red diagonal on top but one yellow
    assert(!boardState()
                .dropPiece(0, boardPiece::YELLOW)
                .value()
                .dropPiece(0, boardPiece::YELLOW)
                .value()
                .dropPiece(0, boardPiece::YELLOW)
                .value()
                .dropPiece(1, boardPiece::YELLOW)
                .value()
                .dropPiece(1, boardPiece::YELLOW)
                .value()
                .dropPiece(2, boardPiece::YELLOW)
                .value()
                .dropPiece(0, boardPiece::RED)
                .value()
                .dropPiece(1, boardPiece::RED)
                .value()
                .dropPiece(2, boardPiece::YELLOW)
                .value()
                .dropPiece(3, boardPiece::RED)
                .value()
                .getWinner());
  } catch (const std::bad_optional_access& e) {
    assert(false);
  }
}

void diagUp() {
  try {
    // Yellow 3 pyramid with incomplete red diagonal on top
    assert(!boardState()
                .dropPiece(3, boardPiece::YELLOW)
                .value()
                .dropPiece(3, boardPiece::YELLOW)
                .value()
                .dropPiece(3, boardPiece::YELLOW)
                .value()
                .dropPiece(2, boardPiece::YELLOW)
                .value()
                .dropPiece(2, boardPiece::YELLOW)
                .value()
                .dropPiece(1, boardPiece::YELLOW)
                .value()
                .dropPiece(3, boardPiece::RED)
                .value()
                .dropPiece(2, boardPiece::RED)
                .value()
                .dropPiece(1, boardPiece::RED)
                .value()
                .getWinner());
    // Yellow 3 pyramid with red diagonal on top
    assert(boardState()
               .dropPiece(3, boardPiece::YELLOW)
               .value()
               .dropPiece(3, boardPiece::YELLOW)
               .value()
               .dropPiece(3, boardPiece::YELLOW)
               .value()
               .dropPiece(2, boardPiece::YELLOW)
               .value()
               .dropPiece(2, boardPiece::YELLOW)
               .value()
               .dropPiece(1, boardPiece::YELLOW)
               .value()
               .dropPiece(3, boardPiece::RED)
               .value()
               .dropPiece(2, boardPiece::RED)
               .value()
               .dropPiece(1, boardPiece::RED)
               .value()
               .dropPiece(0, boardPiece::RED)
               .value()
               .getWinner());
    // Yellow 3 pyramid with almost red diagonal on top but one yellow
    assert(!boardState()
                .dropPiece(3, boardPiece::YELLOW)
                .value()
                .dropPiece(3, boardPiece::YELLOW)
                .value()
                .dropPiece(3, boardPiece::YELLOW)
                .value()
                .dropPiece(2, boardPiece::YELLOW)
                .value()
                .dropPiece(2, boardPiece::YELLOW)
                .value()
                .dropPiece(1, boardPiece::YELLOW)
                .value()
                .dropPiece(3, boardPiece::RED)
                .value()
                .dropPiece(2, boardPiece::RED)
                .value()
                .dropPiece(1, boardPiece::YELLOW)
                .value()
                .dropPiece(0, boardPiece::RED)
                .value()
                .getWinner());
  } catch (const std::bad_optional_access& e) {
    assert(false);
  }
}

void draw() {
  try {
    boardState baseState;

    boardPiece _1 = boardPiece::RED;
    boardPiece _2 = boardPiece::YELLOW;

    for (int16_t row = 0; row < (gridHeight - 1); ++row) {
      baseState = baseState.dropPiece(0, _1)
                      .value()
                      .dropPiece(1, _1)
                      .value()
                      .dropPiece(2, _2)
                      .value()
                      .dropPiece(3, _2)
                      .value()
                      .dropPiece(4, _1)
                      .value()
                      .dropPiece(5, _1)
                      .value()
                      .dropPiece(6, _2)
                      .value();

      std::swap(_1, _2);
    }

    // No draw
    assert(!baseState.getWinner());
    // No draw
    assert(!baseState.dropPiece(0, boardPiece::RED)
                .value()
                .dropPiece(1, boardPiece::RED)
                .value()
                .dropPiece(2, boardPiece::YELLOW)
                .value()
                .dropPiece(3, boardPiece::YELLOW)
                .value()
                .dropPiece(4, boardPiece::RED)
                .value()
                .dropPiece(5, boardPiece::RED)
                .value()
                .getWinner());
    // Draw
    assert(baseState.dropPiece(0, boardPiece::RED)
                .value()
                .dropPiece(1, boardPiece::RED)
                .value()
                .dropPiece(2, boardPiece::YELLOW)
                .value()
                .dropPiece(3, boardPiece::YELLOW)
                .value()
                .dropPiece(4, boardPiece::RED)
                .value()
                .dropPiece(5, boardPiece::RED)
                .value()
                .dropPiece(6, boardPiece::YELLOW)
                .value()
                .getWinner());
  } catch (const std::bad_optional_access& e) {
    assert(false);
  }
}

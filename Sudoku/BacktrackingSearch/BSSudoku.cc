#include "BSSudoku.h"

BSSudoku::BSSudoku(int& it) : it(it) {}

bool BSSudoku::Solve() {
  it = 1;
  return Recursive(0, 0);
}

bool BSSudoku::Recursive(int r, int c) {
  // find next grid
  while (true) {
    if (puzzle[r][c] == 0) break;
    if (++c == 9) c = 0, r++;
    if (r == 9) {
      return true;
    }
  }

  // search and check
  for (int i = 1; i <= 9; i++) {
    puzzle[r][c] = i;
    if (Check(r, c)) {
      bool done = Recursive(r, c);
      if (done) return true;
    }
    puzzle[r][c] = 0;
  }
  return false;
}

bool BSSudoku::Check(int r, int c) {
  // check row
  for (int i = 0; i < 9; i++) {
    if (r == i) continue;
    if (puzzle[i][c] == puzzle[r][c]) {
      it++;
      return false;
    }
  }

  // check col
  for (int i = 0; i < 9; i++) {
    if (c == i) continue;
    if (puzzle[r][i] == puzzle[r][c]) {
      it++;
      return false;
    }
  }

  // check grid
  int x = r / 3, y = c / 3;
  for (int i = x * 3; i < x * 3 + 3; i++) {
    for (int j = y * 3; j < y * 3 + 3; j++) {
      if (i == r && j == c) continue;
      if (puzzle[r][c] == puzzle[i][j]) {
        it++;
        return false;
      }
    }
  }

  return true;
}

void BSSudoku::ImportPuzzle(const char* input) {
  ifstream file(input);
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      file >> puzzle[i][j];
    }
  }
}

void BSSudoku::ExportResult(const char* output) {
  ofstream file(output);
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      file << puzzle[i][j] << " ";
    }
    file << std::endl;
  }
}
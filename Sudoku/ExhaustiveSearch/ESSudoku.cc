#include "ESSudoku.h"

ESSudoku::ESSudoku(int& it) : it(it) { solved = false; }

bool ESSudoku::Solve() {
  it = 1;
  FillNext(0, 0);
  return solved;
}

void ESSudoku::FillNext(int r, int c) {
  if (it >= 50000000) return;

  if (solved) {
    return;
  }

  // find next grid
  while (true) {
    if (puzzle[r][c] == 0) break;
    if (++c == 9) c = 0, r++;
    if (r == 9) {
      solved = Check();
      return;
    }
  }

  // search
  for (int i = 1; i <= 9; i++) {
    puzzle[r][c] = i;
    FillNext(r, c);
    if (solved) return;
    puzzle[r][c] = 0;
  }
}

bool ESSudoku::Check() {
  int row_cnt[9][10] = {0};
  int col_cnt[9][10] = {0};
  int grid_cnt[3][3][10] = {0};
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      int n = puzzle[i][j];

      if (++row_cnt[i][n] == 2) {
        it++;
        return false;
      }

      if (++col_cnt[j][n] == 2) {
        it++;
        return false;
      }

      if (++grid_cnt[i / 3][j / 3][n] == 2) {
        it++;
        return false;
      }
    }
  }
  return true;
}

void ESSudoku::ImportPuzzle(const char* input) {
  ifstream file(input);
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      file >> puzzle[i][j];
    }
  }
}

void ESSudoku::ExportResult(const char* output) {
  ofstream file(output);
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      file << puzzle[i][j] << " ";
    }
    file << std::endl;
  }
}
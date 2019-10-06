#include "MRVSudoku.h"

#define log()                                     \
  for (int i = 0; i < 9; i++) {                   \
    for (int j = 0; j < 9; j++) {                 \
      printf("(%d,%d)%d: ", i, j, poss[i][j][0]); \
      for (int k = 1; k <= 9; k++) {              \
        if (poss[i][j][k] == 1) {                 \
          printf("%d", k);                        \
        }                                         \
      }                                           \
      printf("\n");                               \
    }                                             \
    printf("\n");                                 \
  }

MRVSudoku::MRVSudoku(int& it) : it(it) {}

bool MRVSudoku::Solve() {
  it = 1;
  return Recursive();
}

bool MRVSudoku::Recursive() {
  // find next grid
  int r = 0, c = 0, min = 9;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (puzzle[i][j] == 0 && poss[i][j][0] < min) {
        r = i, c = j, min = poss[i][j][0];
      }
    }
  }

  if (puzzle[r][c] != 0) {
    return true;
  }

  // fill and check
  for (int i = 1; i <= 9; i++) {
    if (poss[r][c][i] == 0) {
      continue;
    }
    puzzle[r][c] = i;

    int changes_row[10], changes_col[10], changes_grid[10];
    memset(changes_row, 0, sizeof(int) * 10);
    memset(changes_col, 0, sizeof(int) * 10);
    memset(changes_grid, 0, sizeof(int) * 10);

    bool work = Push(r, c, i, changes_row, changes_col, changes_grid);

    if (work) {
      bool done = Recursive();
      if (done) {
        return true;
      }
    }

    Pop(r, c, i, changes_row, changes_col, changes_grid);
    puzzle[r][c] = 0;
  }
  return false;
}

bool MRVSudoku::Push(int r, int c, int n, int changes_row[10],
                     int changes_col[10], int changes_grid[10]) {
  for (int i = 0; i < 9; i++) {
    // update row
    if (puzzle[r][i] == 0 && poss[r][i][n] == 1) {
      changes_row[++changes_row[0]] = i;
      poss[r][i][n] = 0;
      poss[r][i][0]--;
      if (poss[r][i][0] == 0) {
        it++;
        return false;
      }
    }

    // update col
    if (puzzle[i][c] == 0 && poss[i][c][n] == 1) {
      changes_col[++changes_col[0]] = i;
      poss[i][c][n] = 0;
      poss[i][c][0]--;
      if (poss[i][c][0] == 0) {
        it++;
        return false;
      }
    }

    // update grid
    int x = r / 3 * 3 + i / 3;
    int y = c / 3 * 3 + i % 3;
    if (puzzle[x][y] == 0 && poss[x][y][n] == 1) {
      changes_grid[++changes_grid[0]] = x * 9 + y;
      poss[x][y][n] = 0;
      poss[x][y][0]--;
      if (poss[x][y][0] == 0) {
        it++;
        return false;
      }
    }
  }
  return true;
}

void MRVSudoku::Pop(int r, int c, int n, int changes_row[10],
                    int changes_col[10], int changes_grid[10]) {
  // restore row
  for (int i = 1; i <= changes_row[0]; i++) {
    int j = changes_row[i];
    poss[r][j][n] = 1;
    poss[r][j][0]++;
  }

  // restore col
  for (int i = 1; i <= changes_col[0]; i++) {
    int j = changes_col[i];
    poss[j][c][n] = 1;
    poss[j][c][0]++;
  }

  // restore grid
  for (int i = 1; i <= changes_grid[0]; i++) {
    int j = changes_grid[i];
    int x = j / 9;
    int y = j % 9;
    poss[x][y][n] = 1;
    poss[x][y][0]++;
  }
}

void MRVSudoku::ImportPuzzle(const char* input) {
  bool row[9][10], col[9][10], grid[3][3][10];

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 10; j++) {
      row[i][j] = false;
      col[i][j] = false;
      grid[i / 3][i % 3][j] = false;
    }
  }

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      puzzle[i][j] = 0;
      poss[i][j][0] = 9;
      for (int k = 1; k <= 9; k++) {
        poss[i][j][k] = 1;
      }
    }
  }

  ifstream file(input);

  for (int i = 0, n; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      file >> n;
      puzzle[i][j] = n;
      row[i][n] = true;
      col[j][n] = true;
      grid[i / 3][j / 3][n] = true;
    }
  }

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (puzzle[i][j] == 0) {
        for (int k = 1; k <= 9; k++) {
          if (row[i][k] || col[j][k] || grid[i / 3][j / 3][k]) {
            poss[i][j][k] = 0;
            poss[i][j][0]--;
          }
        }
      }
    }
  }
}

void MRVSudoku::ExportResult(const char* output) {
  ofstream file(output);
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      file << puzzle[i][j] << " ";
    }
    file << std::endl;
  }
}
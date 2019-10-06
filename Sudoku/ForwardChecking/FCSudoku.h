#ifndef __FCSUDOKU__
#define __FCSUDUKU__ 1

#include <cstring>
#include <fstream>
#include <list>
using std::ifstream;
using std::list;
using std::ofstream;

class FCSudoku {
 public:
  FCSudoku(int& it);
  bool Solve();
  void ImportPuzzle(const char* input);
  void ExportResult(const char* output);

 private:
  bool Recursive(int r, int c);
  bool Push(int r, int c, int n, int changes_row[10], int changes_col[10],
            int changes_grid[10]);
  void Pop(int r, int c, int n, int changes_row[10], int changes_col[10],
           int changes_grid[10]);

 private:
  int& it;
  int poss[9][9][10];
  int puzzle[9][9];
};

#endif

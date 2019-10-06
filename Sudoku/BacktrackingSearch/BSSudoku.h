#ifndef __BSSUDOKU__
#define __BSSUDUKU__ 1

#include <fstream>
using std::ifstream;
using std::ofstream;

class BSSudoku {
 public:
  BSSudoku(int& it);
  bool Solve();
  void ImportPuzzle(const char* input);
  void ExportResult(const char* output);

 private:
  bool Recursive(int r, int c);
  bool Check(int r, int c);

 private:
  int& it;
  int puzzle[9][9];
};

#endif
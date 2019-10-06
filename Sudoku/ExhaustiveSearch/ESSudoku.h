#ifndef __ESSUDOKU__
#define __ESSUDUKU__ 1

#include <fstream>
using std::ifstream;
using std::ofstream;

class ESSudoku {
 public:
  ESSudoku(int& it);
  bool Solve();
  void ImportPuzzle(const char* input);
  void ExportResult(const char* output);

 private:
  void FillNext(int r, int c);
  bool Check();

 private:
  int&it;
  bool solved;
  int puzzle[9][9];
};

#endif

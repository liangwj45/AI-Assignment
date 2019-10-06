#include "BacktrackingSearch/BSSudoku.h"
#include "ExhaustiveSearch/ESSudoku.h"
#include "ForwardChecking/FCSudoku.h"
#include "MinimumRemainingValues/MRVSudoku.h"

#include <windows.h>
#include <cstring>
#include <iostream>
using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
  const char* path = argc > 1 ? argv[1] : "./puzzle/puzzle.txt";
  cout << "test: " << path << endl;

  int it;
  bool solved;
  LARGE_INTEGER freq, start, end;
  QueryPerformanceFrequency(&freq);  // 获取时钟周期

  ESSudoku es(it);
  es.ImportPuzzle(path);
  QueryPerformanceCounter(&start);
  solved = es.Solve();
  QueryPerformanceCounter(&end);
  es.ExportResult("./output/output.txt");
  cout << (solved ? "ES solved" : "ES  Failed") << ", time used: "
       << 1000 * (double)(end.QuadPart - start.QuadPart) / freq.QuadPart
       << " ms\titerations: " << it << endl;

  BSSudoku bs(it);
  bs.ImportPuzzle(path);
  QueryPerformanceCounter(&start);
  solved = bs.Solve();
  QueryPerformanceCounter(&end);
  bs.ExportResult("./output/output.txt");
  cout << (solved ? "BS  solved" : "BS  Failed") << ", time used: "
       << 1000 * (double)(end.QuadPart - start.QuadPart) / freq.QuadPart
       << " ms\titerations: " << it << endl;

  FCSudoku fc(it);
  fc.ImportPuzzle(path);
  QueryPerformanceCounter(&start);
  solved = fc.Solve();
  QueryPerformanceCounter(&end);
  fc.ExportResult("./output/output.txt");
  cout << (solved ? "FC  solved" : "FC  Failed") << ", time used: "
       << 1000 * (double)(end.QuadPart - start.QuadPart) / freq.QuadPart
       << " ms\titerations: " << it << endl;

  MRVSudoku mrv(it);
  mrv.ImportPuzzle(path);
  QueryPerformanceCounter(&start);
  solved = mrv.Solve();
  QueryPerformanceCounter(&end);
  mrv.ExportResult("./output/output.txt");
  cout << (solved ? "MRV solved" : "MRV Failed") << ", time used: "
       << 1000 * (double)(end.QuadPart - start.QuadPart) / freq.QuadPart
       << " ms\titerations: " << it << endl;
}
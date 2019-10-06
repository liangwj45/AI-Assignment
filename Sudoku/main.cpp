#include <iostream>
#include "iomanip"
#include "string"
#include "vector"

#include <time.h>

using namespace std;

class Sudoku {
 private:
  bool row[9][9] = {}, col[9][9] = {},
       sGrid[9][9] = {};  //用于记录行列以及小格子里面有没有填数字
  int poss[9][9];         //用于记录该位置可能性的大小
  int count;              //用于记录总数，判断是否停止查找
  string question;        //待处理的字符串
  //    int clock = 0;                         //用于计算迭代次数
 public:
  Sudoku(string aimQ) {
    count = 0;

    for (int i = 0; i < 9; i++)
      for (int j = 0; j < 9; j++) poss[i][j] = 9;

    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (aimQ[i * 9 + j] != '.') {
          count++;
          row[i][aimQ[i * 9 + j] - '1'] = true;
          col[j][aimQ[i * 9 + j] - '1'] = true;
          sGrid[(i / 3) * 3 + (j / 3) % 3][aimQ[i * 9 + j] - '1'] = true;
        }
        question += aimQ[i * 9 + j];
      }
    }
    for (int i = 0; i < 9; i++)
      for (int j = 0; j < 9; j++) {
        int index = (i / 3) * 3 + (j / 3) % 3;
        for (int c = 0; c < 9; c++) {
          if (row[i][c] || col[j][c] || sGrid[index][c]) poss[i][j]--;
        }
      }
  }
  bool upDataPoss(int i, int j, int c, bool upOrBack) {
    bool judge = true;

    for (int k = 0; k < 9; k++) {
      if (!col[k][c] && !sGrid[(i / 3) * 3 + (k / 3) % 3][c]) {
        if (upOrBack) {
          poss[i][k]--;
          if (k != j && question[i * 9 + k] == '.' && !poss[i][k])
            judge = false;
        } else
          poss[i][k]++;
      }
      if (!row[k][c] && !sGrid[(k / 3) * 3 + (j / 3) % 3][c]) {
        if (upOrBack) {
          poss[k][j]--;
          if (k != i && question[k * 9 + j] == '.' && !poss[k][j])
            judge = false;
        } else
          poss[k][j]++;
      }
      int sr = (i / 3) * 3, sc = (j / 3) * 3, si = k / 3, sj = k % 3;
      if ((sr + si) != i && (sc + sj) != j && !row[sr + si][c] &&
          !col[sc + sj][c]) {
        if (upOrBack) {
          poss[sr + si][sc + sj]--;
          if (question[(sr + si) * 9 + sc + sj] == '.' &&
              !poss[sr + si][sc + sj])
            judge = false;
        } else
          poss[sr + si][sc + sj]++;
      }
    }
    return judge;
  }

  int Find() {
    int min = 10, r = 0, c = 0;
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (question[i * 9 + j] == '.') {
          min = min < poss[i][j] ? min : poss[i][j];
          r = i;
          c = j;
          if (min == 1) return r * 9 + c;
        }
      }
    }
    return r * 9 + c;
  }

  void solveSudoku() {
    if (count == 81) return;
    //        clock++;
    int n = Find();  //找到要填的位置
    int i = n / 9, j = n % 9;
    int index = (i / 3) * 3 + (j / 3) % 3;
    int judge = true;
    for (int c = 0; c < 9; c++) {
      if (!row[i][c] && !col[j][c] && !sGrid[index][c]) {
        judge = upDataPoss(i, j, c, 1);
        row[i][c] = true;
        col[j][c] = true;
        sGrid[index][c] = true;
        question[n] = c + '1';
        count++;
        if (judge) solveSudoku();
        if (count == 81) return;

        count--;
        question[n] = '.';
        row[i][c] = false;
        col[j][c] = false;
        sGrid[index][c] = false;
        judge = upDataPoss(i, j, c, 0);
      }
    }
  }
  void print(bool output) {
    if (!output) {
      cout << question << endl;
    } else {
      for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
          cout << setw(4) << question[i * 9 + j];
        }
        cout << endl;
      }
    }
  }
};

#include <windows.h>
int main() {
  string question =
      "..............3.85..1.2.......5.7.....4...1...9.......5......73..2.1...."
      "....4...9";
  Sudoku test(question);
  LARGE_INTEGER freq, start, end;
  QueryPerformanceFrequency(&freq);  // 获取时钟周期
  QueryPerformanceCounter(&start);   // 获取时钟计数
  test.solveSudoku();
  QueryPerformanceCounter(&end);
  cout << "time used: "
       << (double)(end.QuadPart - start.QuadPart) / freq.QuadPart << endl;
  return 0;
}

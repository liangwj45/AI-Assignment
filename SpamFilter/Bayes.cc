#include "Bayes.h"
#include <fstream>
#include <iostream>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::pair;

namespace AI_assignment {
void Bayes::AddTrainingData(const char* const dataPath,
                            const char* const labelPath) {
  int lbl, eid, wid, wc;
  ifstream lf(labelPath), df(dataPath);
  while (!lf.eof()) {
    lf >> lbl;
    emails.insert(pair<int, int>(emails.size() + 1, lbl));
    spam_count += lbl, ham_count += (!lbl);
  }
  while (!df.eof()) {
    df >> eid >> wid >> wc;
    if (emails[eid]) {
      if (count_in_spam.find(wid) == count_in_spam.end())
        count_in_spam.insert(pair<int, int>(wid, 0));
      count_in_spam[wid]++;
    } else {
      if (count_in_ham.find(wid) == count_in_ham.end())
        count_in_ham.insert(pair<int, int>(wid, 0));
      count_in_ham[wid]++;
    }
  }
}

double Bayes::Test(const char* const testDataPath,
                   const char* const testLabelPath,
                   const char* const outPutPath) {
  int eid, wid, wc;
  map<int, double> r1, r2;
  double pa = (double)spam_count / (spam_count + ham_count);
  ifstream df(testDataPath);
  while (!df.eof()) {
    df >> eid >> wid >> wc;
    if (r1.find(eid) == r1.end()) {
      r1.insert(pair<int, double>({eid, pa}));
      r2.insert(pair<int, double>({eid, 1 - pa}));
    }
    double pba = (count_in_spam[wid] + lambda) /
                 (count_in_spam[wid] + count_in_ham[wid] +
                  lambda * count_in_spam.size());
    double pba2 =
        (count_in_ham[wid] + lambda) /
        (count_in_spam[wid] + count_in_ham[wid] + lambda * count_in_ham.size());
    r1[eid] *= pba, r2[eid] *= pba2;
  }

  map<int, int> r3;
  for (auto each : r1) {
    r3.insert(pair<int, int>(each.first, (each.second > r2[each.first])));
  }

  int lbl, id = 1, cor = 0;
  ifstream lf(testLabelPath);
  while (!lf.eof()) {
    lf >> lbl;
    if (lbl == r3[id++]) cor++;
  }

  return (double)cor / id;
}
}  // namespace AI_assignment
#include <map>
using std::map;

namespace AI_assignment {
class Bayes {
 public:
  void AddTrainingData(const char* const dataPath, const char* const labelPath);
  double Test(const char* const testDataPath, const char* const testLabelPath,
              const char* const outPutPath);

 private:
  map<int, int> emails;
  map<int, int> count_in_spam;
  map<int, int> count_in_ham;
  int spam_count = 0;
  int ham_count = 0;
  double lambda = 1e-10;
};
}  // namespace AI_assignment
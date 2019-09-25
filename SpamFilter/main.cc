#include <iostream>
#include "Bayes.h"
using namespace AI_assignment;

class Test {
 public:
  double test1() {
    Bayes test1;
    test1.AddTrainingData("./DataPrepared/train-features-50.txt",
                          "./DataPrepared/train-labels-50.txt");
    return test1.Test("./DataPrepared/test-features.txt",
                      "./DataPrepared/test-labels.txt",
                      "./result/test1-output.txt");
  }

  double test2() {
    Bayes test1;
    test1.AddTrainingData("./DataPrepared/train-features-100.txt",
                          "./DataPrepared/train-labels-100.txt");
    return test1.Test("./DataPrepared/test-features.txt",
                      "./DataPrepared/test-labels.txt",
                      "./result/test2-output.txt");
  }

  double test3() {
    Bayes test1;
    test1.AddTrainingData("./DataPrepared/train-features-400.txt",
                          "./DataPrepared/train-labels-400.txt");
    return test1.Test("./DataPrepared/test-features.txt",
                      "./DataPrepared/test-labels.txt",
                      "./result/test3-output.txt");
  }

  double test4() {
    Bayes test1;
    test1.AddTrainingData("./DataPrepared/train-features.txt",
                          "./DataPrepared/train-labels.txt");
    return test1.Test("./DataPrepared/test-features.txt",
                      "./DataPrepared/test-labels.txt",
                      "./result/test4-output.txt");
  }
};

int main() {
  Test test;
  std::cout << "Test1\t" << test.test1() << std::endl;
  std::cout << "Test2\t" << test.test2() << std::endl;
  std::cout << "Test3\t" << test.test3() << std::endl;
  std::cout << "Test4\t" << test.test4() << std::endl;
}
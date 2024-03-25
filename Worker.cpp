//
// Created by Elijah on 3/20/2024.
//
#include "Worker.hpp"

void Worker::doWork() {


  int batchSize = 5000;
  minimizer.Train(batchSize);
  std::array<std::vector<float>,169> strats;
  for (int row = 0; row < 13; ++row) {
    for (int col = 0; col < 13; ++col) {
      strats[row*13+col] = minimizer.getNodeInformation(std::format("{}",row*13+col))[2];
    }
  }
  emit resultReady(strats);
}
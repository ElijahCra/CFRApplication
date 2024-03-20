//
// Created by Elijah on 3/20/2024.
//
#include "Worker.hpp"

void Worker::doWork() {

  CFR::RegretMinimizer<Preflop::Game> regret_minimizer;
  int batchSize = 5000;
  regret_minimizer.Train(batchSize);
  std::array<std::vector<float>,169> strats;
  for (int row = 0; row < 13; ++row) {
    for (int col = 0; col < 13; ++col) {
      strats[row*13+col] = regret_minimizer.getNodeAverageStrategy(std::format("{}",row*13+col));
    }
  }
  emit resultReady(strats);
}
//
// Created by Elijah on 3/20/2024.
//
#include "Worker.hpp"

void Worker::doWork(uint32_t epochs, uint32_t iterations) {

  for (int i=0; i < epochs; ++i){
    if (QThread::currentThread()->isInterruptionRequested()) {return;}
    minimizer.Train(iterations);
    std::array<std::vector<float>,169> strats;
    for (int row = 0; row < 13; ++row) {
      for (int col = 0; col < 13; ++col) {
        strats[row*13+col] = minimizer.getNodeInformation(std::format("{}",row*13+col))[2];
      }
    }
    emit resultReady(strats);
  }
}
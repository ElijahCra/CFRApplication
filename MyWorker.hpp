//
// Created by Elijah Crain on 5/13/24.
//

#ifndef CFRAPP_MYWORKER_HPP_
#define CFRAPP_MYWORKER_HPP_

#include <QtCore>
#include "Worker.hpp"
#include "2PlayerCFR/CFR/RegretMinimizer.hpp"
#include "2PlayerCFR/Game/GameImpl/Preflop/Game.hpp"
class MyWorker : public Worker
{
  Q_OBJECT
  signals:
    void resultReady(const std::array<std::vector<float>, 169>& strats);
 private:
  CFR::RegretMinimizer<Preflop::Game> minimizer;

 public:
  using Worker::Worker;

  void doWork(uint32_t epochs, uint32_t iterations)
  {
    minimizer.printPreflopStats();
    minimizer.setCancelled(false);
    using enum Worker::State;
    if (state == PAUSED)
      // treat as resume
      state = RUNNING;
    state = RUNNING;
    qDebug() << "started";
    //emit started();

    // This loop simulates the actual work
    for (auto i = 0u; i <epochs;  ++i) {
      //QThread::msleep(100);
      if (isCancelled()) break;
      if (PAUSED == state) {while (PAUSED == state){QThread::msleep(200);}}
      qDebug() << i;
      
      // Train in smaller batches to allow for more frequent cancellation checks
      const uint32_t batchSize = std::min(iterations, 100u);
      uint32_t remaining = iterations;
      
      while (remaining > 0 && !isCancelled()) {
        uint32_t currentBatch = std::min(remaining, batchSize);
        minimizer.setCancelled(isCancelled()); // Pass cancellation to minimizer
        minimizer.Train(currentBatch);
        remaining -= currentBatch;
        
        // Check for cancellation between batches
        if (isCancelled()) break;
      }
      
      if (isCancelled()) break;
      
      std::array<std::vector<float>,169> strats;
      for (int row = 0; row < 13; ++row) {
        for (int col = 0; col < 13; ++col) {
          strats[row*13+col] = minimizer.getNodeInformation(std::format("{}",row*13+col))[2];
        }
      }
      emit resultReady(strats);
    }

    // Final flush to ensure all nodes are persisted
    minimizer.flushStorageCache();
    qDebug() << "finished";
    //emit finished();
  }
};

#endif //CFRAPP_MYWORKER_HPP_

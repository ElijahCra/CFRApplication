//
// Created by Elijah Crain on 3/18/24.
//

#ifndef CFRAPP__CFRTHREAD_HPP_
#define CFRAPP__CFRTHREAD_HPP_

#include <QtCore>
#include "2PlayerCFR/CFR/RegretMinimizer.hpp"
#include "2PlayerCFR/Game/GameImpl/Preflop/Game.hpp"
class CFRThread : public QThread
{
  Q_OBJECT

 public:
  CFRThread(QObject *parent = nullptr) : QThread(parent) {}

  void run() override {
    CFR::RegretMinimizer<Preflop::Game> regret_minimizer;
    int maxIterations = 5000;
      regret_minimizer.Train(5000);
      for (int row = 0; row < 13; ++row) {
        for (int col = 0; col < 13; ++col) {
          auto strat = regret_minimizer.getNodeStrategy(std::format("{}",row*13+col));

          float value1 = strat[0];
          float value2 = strat[1];
          float value3 = strat[2];

          // Emit a signal to update the square at (row, col)
          emit squareUpdated(row, col, value1, value2, value3);

          // Add a small delay to visualize the updates
          QThread::msleep(100);
        }
      }
  }

  signals:
      void squareUpdated(int row, int col, float value1, float value2, float value3);
};

#endif //CFRAPP__CFRTHREAD_HPP_

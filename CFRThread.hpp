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
    int batchSize = 5000;
      regret_minimizer.Train(batchSize);
      std::array<std::vector<float>,169> strats;
      for (int row = 0; row < 13; ++row) {
        for (int col = 0; col < 13; ++col) {
          strats[row*13+col] = regret_minimizer.getNodeAverageStrategy(std::format("{}",row*13+col));

          // Emit a signal to update the square at (row, col)
          emit squareUpdated(strats);

        }
      }
  }

  signals:
      void squareUpdated(std::array<std::vector<float>,169> strats);
};

#endif //CFRAPP__CFRTHREAD_HPP_

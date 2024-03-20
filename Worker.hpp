//
// Created by Elijah Crain on 3/19/24.
//

#ifndef CFRAPP__WORKER_HPP_
#define CFRAPP__WORKER_HPP_

#include <QtCore>
#include "2PlayerCFR/CFR/RegretMinimizer.hpp"
#include "2PlayerCFR/Game/GameImpl/Preflop/Game.hpp"
class Worker : public QObject
{
 Q_OBJECT

 public slots:
  void doWork(const QString &parameter) {

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

 signals:
  void resultReady(const std::array<std::vector<float>,169> strats);
};

class Controller : public QObject
{
 Q_OBJECT
  QThread workerThread;
 public:
  Controller() {
    auto *worker = new Worker;
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &Controller::operate, worker, &Worker::doWork);
    connect(worker, &Worker::resultReady, this, &Controller::handleResults);
    workerThread.start();
  }
  ~Controller() {
    workerThread.quit();
    workerThread.wait();
  }
 public slots:
  void handleResults(const std::array<std::vector<float>,169>&);
 signals:
  void operate(const QString &);
};

#endif //CFRAPP__WORKER_HPP_

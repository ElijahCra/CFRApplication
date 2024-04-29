//
// Created by Elijah Crain on 3/19/24.
//

#ifndef CFRAPP_WORKER_HPP_
#define CFRAPP_WORKER_HPP_

#include <QtCore>
#include "2PlayerCFR/CFR/RegretMinimizer.hpp"
#include "2PlayerCFR/Game/GameImpl/Preflop/Game.hpp"
class Worker : public QObject
{
 Q_OBJECT

 public slots:
  void doWork(uint32_t epochs, uint32_t iterations);

 signals:
  void resultReady(std::array<std::vector<float>,169> strats);
private:
  CFR::RegretMinimizer<Preflop::Game> minimizer;
};


#endif //CFRAPP_WORKER_HPP_

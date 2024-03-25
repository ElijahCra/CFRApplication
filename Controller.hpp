//
// Created by Elijah on 3/20/2024.
//

#ifndef CFRAPP__CONTROLLER_HPP_
#define CFRAPP__CONTROLLER_HPP_

#include "Worker.hpp"
#include "RegretMinimizer.hpp"
class Controller : public QObject
{
 Q_OBJECT
  QThread workerThread;
 public:
  explicit Controller();
  ~Controller();

 public slots:
  void handleResults(const std::array<std::vector<float>,169>&);
 signals:
  void operate();
  void resultsReadyForUI(const std::array<std::vector<float>, 169>&);
};

#endif //CFRAPP__CONTROLLER_HPP_

//
// Created by Elijah on 3/20/2024.
//

#ifndef CFRAPP_CONTROLLER_HPP_
#define CFRAPP_CONTROLLER_HPP_

#include "Worker.hpp"
#include "RegretMinimizer.hpp"
class Controller final : public QObject
{
 Q_OBJECT
  QThread workerThread;
 public:
  explicit Controller();
  ~Controller() override;

 public slots:
  void handleResults(const std::array<std::vector<float>,169>&);
  void handleStop();
 signals:
  void operate(uint32_t epochs, uint32_t iterations);
  void resultsReadyForUI(const std::array<std::vector<float>, 169>&);
};

#endif //CFRAPP_CONTROLLER_HPP_

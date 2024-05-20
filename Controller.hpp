//
// Created by Elijah on 3/20/2024.
//

#ifndef CFRAPP_CONTROLLER_HPP_
#define CFRAPP_CONTROLLER_HPP_

#include "Worker.hpp"
#include "RegretMinimizer.hpp"
#include "MyWorker.hpp"
class Controller final : public QObject
{
 Q_OBJECT
  QThread thread;
 public:
  explicit Controller();
  ~Controller() override;

  MyWorker* worker = new MyWorker();

 public slots:
  void handleResults(const std::array<std::vector<float>,169>& strats);
  void handlePause() const;
  void handleCancel() const;
  void handleResume() const;
 signals:
  void operate(uint32_t epochs, uint32_t iterations);
  void resultsReadyForUI(const std::array<std::vector<float>, 169>&);
};

#endif //CFRAPP_CONTROLLER_HPP_

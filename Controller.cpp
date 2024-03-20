//
// Created by Elijah on 3/20/2024.
//

#include "Controller.hpp"
Controller::Controller() {
  auto *worker = new Worker;
  worker->moveToThread(&workerThread);
  connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
  connect(this, &Controller::operate, worker, &Worker::doWork);
  connect(worker, &Worker::resultReady, this, &Controller::handleResults);
  workerThread.start();
}
Controller::~Controller() {
  workerThread.quit();
  workerThread.wait();
}

void Controller::handleResults(const std::array<std::vector<float>, 169>& strats) {
  // Do any necessary processing or manipulation of 'strats' if needed
  emit resultsReadyForUI(strats);
}
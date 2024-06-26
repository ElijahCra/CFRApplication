//
// Created by Elijah on 3/20/2024.
//

#include "Controller.hpp"
#include "MyWorker.hpp"
Controller::Controller() {
  worker->moveToThread(&thread);
  //connect(worker, &MyWorker::finished, worker, &QObject::deleteLater);
  connect(worker, &QObject::destroyed, &thread, &QThread::quit);
  connect(this, &Controller::operate, worker, &MyWorker::doWork);
  connect(worker, &MyWorker::resultReady, this, &Controller::handleResults);
  thread.start();
}

Controller::~Controller() {
  thread.quit();
  thread.wait();
}

void Controller::handleResults(const std::array<std::vector<float>, 169>& strats) {
  // Do any necessary processing or manipulation of 'strats' if needed
  emit resultsReadyForUI(strats);
}

void Controller::handleCancel() const {
  worker->cancel();
}

void Controller::handlePause() const {
  worker->pause();
}

void Controller::handleResume() const {
  worker->resume();
}
//
// Created by Elijah Crain on 3/19/24.
//

#ifndef CFRAPP_WORKER_HPP_
#define CFRAPP_WORKER_HPP_

#include <QtCore>
#include <QAbstractEventDispatcher>
#include <QObject>
#include <QThread>
#include <QDebug>

class Worker : public QObject
{
 Q_OBJECT

 public:
  explicit Worker(QObject *parent = 0)
      : QObject(parent)
  {
  }

 signals:
  //void started();
  void finished();

 public slots:
  void pause()
  {
    auto const dispatcher = QThread::currentThread()->eventDispatcher();
    if (!dispatcher) {
      qCritical() << "thread with no dispatcher";
      return;
    }

    if (state != State::RUNNING)
      return;

    state = State::PAUSED;
    qDebug() << "paused";
    do {
      dispatcher->processEvents(QEventLoop::WaitForMoreEvents);
    } while (state == State::PAUSED);
  }

  void resume()
  {
    if (state == State::PAUSED) {
      state = State::RUNNING;
      qDebug() << "resumed";
    }
  }

  void cancel() {
    if (state != State::IDLE) {
      state = State::IDLE;
      qDebug() << "cancelled";
    }
  }

 protected:

  enum class State:int { IDLE=0, RUNNING, PAUSED };
  State state = State::IDLE;

  [[nodiscard]] bool isCancelled() const {
    auto const dispatcher = QThread::currentThread()->eventDispatcher();
    if (!dispatcher) {
      qCritical() << "thread with no dispatcher";
      return false;
    }
    dispatcher->processEvents(QEventLoop::AllEvents);
    return state == State::IDLE;
  }

};

#endif //CFRAPP_WORKER_HPP_

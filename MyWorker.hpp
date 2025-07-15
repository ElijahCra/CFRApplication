//
// Created by Elijah Crain on 5/13/24.
//

#ifndef CFRAPP_MYWORKER_HPP_
#define CFRAPP_MYWORKER_HPP_

#include <QtCore>
#include "Worker.hpp"
#include "2PlayerCFR/CFR/RegretMinimizer.hpp"
#include "2PlayerCFR/CFR/MultiThreadedTrainer.hpp"
#include "2PlayerCFR/Game/GameImpl/Preflop/Game.hpp"
#include "Storage/HybridNodeStorage.hpp"
#include "Storage/MapNodeStorage.hpp"
#include "Storage/ShardedLRUCache.hpp"
#include "Storage/LRUList.hpp"
#include <memory>

template<typename K, typename V> using MyMap = std::unordered_map<K, V>;

enum class TrainingMode {
    SingleThreadedInMem,
    SingleThreadedHybrid,
    MultiThreadedHybrid
};

class MyWorker : public Worker
{
  Q_OBJECT
  signals:
    void resultReady(const std::array<std::vector<float>, 169>& strats);
 private:
  TrainingMode m_trainingMode = TrainingMode::SingleThreadedHybrid;
  
  // Single-threaded minimizers
  std::unique_ptr<CFR::RegretMinimizer<Preflop::Game, CFR::MapNodeStorage>> m_singleMemMinimizer;
  std::unique_ptr<CFR::RegretMinimizer<Preflop::Game, CFR::HybridNodeStorage<CFR::LRUNodeCache<MyMap,LRUList>>>> m_singleHybridMinimizer;
  
  // Multi-threaded trainer
  std::unique_ptr<CFR::MultiThreadedTrainer<Preflop::Game, CFR::HybridNodeStorage<CFR::ShardedLRUCache<MyMap,LRUList>>>> m_multiThreadedTrainer;

 public:
  using Worker::Worker;
  
  void setTrainingMode(TrainingMode mode);
  TrainingMode getTrainingMode() const { return m_trainingMode; }

  void doWork(uint32_t epochs, uint32_t iterations)
  {
    using enum Worker::State;
    if (state == PAUSED)
      // treat as resume
      state = RUNNING;
    state = RUNNING;
    qDebug() << "started";

    // Initialize the appropriate minimizer if not already done
    initializeMinimizer();

    // This loop simulates the actual work
    for (auto i = 0u; i < epochs; ++i) {
      if (isCancelled()) break;
      if (PAUSED == state) {while (PAUSED == state){QThread::msleep(200);}}
      qDebug() << i;
      
      trainIteration(iterations);
      
      std::array<std::vector<float>, 169> strats = getStrategies();
      emit resultReady(strats);
    }

    // Final flush to ensure all nodes are persisted
    flushCache();
    qDebug() << "finished";
  }

private:
  void initializeMinimizer();
  void trainIteration(uint32_t iterations);
  std::array<std::vector<float>, 169> getStrategies();
  void flushCache();
};

#endif //CFRAPP_MYWORKER_HPP_

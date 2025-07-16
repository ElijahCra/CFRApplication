//
// Created by Elijah Crain on 5/13/24.
//

#include "MyWorker.hpp"
#include <format>

void MyWorker::setTrainingMode(TrainingMode mode) {
    if (m_trainingMode == mode) { return;}
    m_trainingMode = mode;
    // Reset minimizers when mode changes
    m_singleMemMinimizer.reset();
    m_singleHybridMinimizer.reset();
    m_multiThreadedTrainer.reset();
}

void MyWorker::setTrainingModeSlot(TrainingMode mode) {
    setTrainingMode(mode);
}

void MyWorker::initializeMinimizer() {
    switch (m_trainingMode) {
        case TrainingMode::SingleThreadedInMem:
            if (!m_singleMemMinimizer) {
                m_singleMemMinimizer = std::make_unique<CFR::RegretMinimizer<Preflop::Game, CFR::MapNodeStorage>>();
            }
            break;
            
        case TrainingMode::SingleThreadedHybrid:
            if (!m_singleHybridMinimizer) {
                m_singleHybridMinimizer = std::make_unique<CFR::RegretMinimizer<Preflop::Game, CFR::HybridNodeStorage<CFR::LRUNodeCache<MyMap,LRUList>>>>();
            }
            break;
            
        case TrainingMode::MultiThreadedHybrid:
            if (!m_multiThreadedTrainer) {
                m_multiThreadedTrainer = std::make_unique<CFR::MultiThreadedTrainer<Preflop::Game, CFR::HybridNodeStorage<CFR::ShardedLRUCache<MyMap,LRUList>>>>();
            }
            break;
    }
}

void MyWorker::trainIteration(uint32_t iterations) {
    switch (m_trainingMode) {
        case TrainingMode::SingleThreadedInMem:
            if (m_singleMemMinimizer) {
                m_singleMemMinimizer->Train(iterations);
            }
            break;
            
        case TrainingMode::SingleThreadedHybrid:
            if (m_singleHybridMinimizer) {
                m_singleHybridMinimizer->Train(iterations);
            }
            break;
            
        case TrainingMode::MultiThreadedHybrid:
            if (m_multiThreadedTrainer) {
                m_multiThreadedTrainer->Train(iterations);
            }
            break;
    }
}

std::array<std::vector<float>, 169> MyWorker::getStrategies() {
    std::array<std::vector<float>, 169> strats;
    
    switch (m_trainingMode) {
        case TrainingMode::SingleThreadedInMem:
            if (m_singleMemMinimizer) {
                for (int row = 0; row < 13; ++row) {
                    for (int col = 0; col < 13; ++col) {
                        strats[row*13+col] = m_singleMemMinimizer->getNodeInformation(std::format("{}",row*13+col))[2];
                    }
                }
            }
            break;
            
        case TrainingMode::SingleThreadedHybrid:
            if (m_singleHybridMinimizer) {
                for (int row = 0; row < 13; ++row) {
                    for (int col = 0; col < 13; ++col) {
                        strats[row*13+col] = m_singleHybridMinimizer->getNodeInformation(std::format("{}",row*13+col))[2];
                    }
                }
            }
            break;
            
        case TrainingMode::MultiThreadedHybrid:
            if (m_multiThreadedTrainer) {
                for (int row = 0; row < 13; ++row) {
                    for (int col = 0; col < 13; ++col) {
                        strats[row*13+col] = m_multiThreadedTrainer->getNodeInformation(std::format("{}",row*13+col))[2];
                    }
                }
            }
            break;
    }
    
    return strats;
}

void MyWorker::flushCache() {
    switch (m_trainingMode) {
        case TrainingMode::SingleThreadedInMem:
            if (m_singleMemMinimizer) {
                m_singleMemMinimizer->flushStorageCache();
            }
            break;
            
        case TrainingMode::SingleThreadedHybrid:
            if (m_singleHybridMinimizer) {
                m_singleHybridMinimizer->flushStorageCache();
            }
            break;
            
        case TrainingMode::MultiThreadedHybrid:
            break;
    }
}
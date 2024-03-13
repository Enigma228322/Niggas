#include <iostream>
#include <niggapool.h>

namespace niggapool {

NiggaPool::NiggaPool(size_t workersCount) {
    while(workersCount > 0) {
        niggas.emplace_back([this](){
            NiggaPool::work();
        });
        --workersCount;
    }
}

NiggaPool::~NiggaPool() {
    {
        std::unique_lock<std::mutex> lock(_mutex);
        weekend = true;
    }
    for (auto& nigga : niggas) {
        nigga.join();
    }
}

void NiggaPool::addTask(callbackType&& callback) {
    {
        std::unique_lock<std::mutex> lock(_mutex);
        tasks.push_back(std::move(callback));
    }
    cond_var.notify_one();
}

size_t NiggaPool::getDirtyTasksNumberInQeue() {
    return tasks.size();
}

void NiggaPool::stopNiggas() {
    {
        std::unique_lock<std::mutex> lock(_mutex);
        weekend = true;
    }
    for (auto& nigga : niggas) {
        nigga.join();
    }
}

void NiggaPool::work() {
    while(!weekend) {
        callbackType callback;
        {
            std::unique_lock<std::mutex> lock(_mutex);
            cond_var.wait(lock, [&](){ return !tasks.empty() || weekend; });
            callback = std::move(tasks.front());
            tasks.pop_back();
        }
        callback();
    }
}
} // namespace workinniggas

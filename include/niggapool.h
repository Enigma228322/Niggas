#pragma once
#include <vector>
#include <mutex>
#include <thread>
#include <functional>

namespace niggapool {

class NiggaPool {
    using callbackType = std::function<void()>;
public:
    NiggaPool(size_t workersCount);

    virtual ~NiggaPool();

    void addTask(callbackType&& callback);

    void goNiggas();

    void stopNiggas();

    size_t getDirtyTasksNumberInQeue();
private:
    std::vector<callbackType> tasks;
    callbackType callback;
    std::mutex _mutex;
    std::vector<std::thread> niggas;
    std::condition_variable cond_var;
    bool weekend = false;

    void work();
};

} // namespace workinniggas

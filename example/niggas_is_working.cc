#include <iostream>
#include <chrono>
#include <niggapool.h>

int main() {
    std::cout << "Create niggas\n";
    auto niggas = niggapool::NiggaPool(100);
    std::cout << "Niggas working on the weekend as usual\n";

    int tasks_num = 1000;
    auto start = std::chrono::high_resolution_clock::now();
    while(tasks_num > 0) {
        niggas.addTask([](){
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << "Nigga " << std::this_thread::get_id() << " is working hard\n";
        });
        --tasks_num;
    }
    while(1) {
        if (niggas.getDirtyTasksNumberInQeue() == 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Time ms: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << '\n';
        }
    }

    std::cout << "Niggas go sleep\n";
    return 0;
}
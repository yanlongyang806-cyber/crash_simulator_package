#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <atomic>
#include <csignal>
#include <cstdlib>

// 日志输出
void log(const std::string &message) {
    std::cout << message << std::endl;
}

// 模拟内存泄漏
void simulateMemoryLeak() {
    std::vector<int*> leakMemory;
    size_t count = 0;
    try {
        while (true) {
            int* memory = new int[1024 * 1024]; // 每次分配 1MB 内存
            leakMemory.push_back(memory);  // 持有内存，模拟泄漏
            count++;
            if (count % 10 == 0) {
                log("[Leak] 内存泄漏模拟中... 已分配内存块: " + std::to_string(count) + " MB");
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(200));  // 每 200 毫秒分配一次
        }
    } catch (const std::exception &e) {
        log("[Leak] 异常: " + std::string(e.what()));
    }
}

// 模拟空指针崩溃
void simulateNullPointerCrash() {
    int* ptr = nullptr;
    log("[NullPointer] 正在访问空指针...");
    std::cout << *ptr << std::endl;  // 访问空指针会导致崩溃
}

// 模拟死锁
void simulateDeadlock() {
    std::mutex mtx1, mtx2;

    std::thread t1([&] {
        std::lock_guard<std::mutex> lock1(mtx1);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::lock_guard<std::mutex> lock2(mtx2);  // 死锁：等待对方锁
    });

    std::thread t2([&] {
        std::lock_guard<std::mutex> lock2(mtx2);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::lock_guard<std::mutex> lock1(mtx1);  // 死锁：等待对方锁
    });

    t1.join();
    t2.join();  // 这两个线程将因相互等待而无法结束，形成死
}

// 模拟崩溃（通过注入）
void simulateCrash() {
    log("[Crash] 模拟崩溃...");
    simulateMemoryLeak();  // 可以选择其他崩溃类型：simulateNullPointerCrash() 或 simulateDeadlock()
}

int main() {
    log("=== 崩溃模拟器启动 ===");

    // 选择运行模拟
    simulateCrash();

    log("=== 崩溃模拟器结束 ===");
    return 0;
}

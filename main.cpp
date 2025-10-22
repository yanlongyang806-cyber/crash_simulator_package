
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <cstdlib>
#include <ctime>

// 模拟内存泄漏
void simulateMemoryLeak() {
    std::vector<int*> leakMemory;
    while (true) {
        int* memory = new int[1000000];  // 分配大量内存
        leakMemory.push_back(memory);
        std::cout << "已分配内存: " << leakMemory.size() * 1000000 * sizeof(int) / (1024 * 1024) << " MB\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // 每 100 毫秒分配一次内存
    }
}

// 模拟空指针访问崩溃
void simulateNullPointerAccess() {
    int* ptr = nullptr;
    std::cout << "模拟空指针访问崩溃...\n";
    std::cout << *ptr << std::endl;  // 访问空指针，会导致崩溃
}

// 模拟线程死锁
std::mutex mtx1, mtx2;
void thread1() {
    std::lock_guard<std::mutex> lock1(mtx1);
    std::cout << "线程 1 锁定 mtx1，尝试锁定 mtx2\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));  // 模拟线程阻塞
    std::lock_guard<std::mutex> lock2(mtx2);
    std::cout << "线程 1 获取到 mtx2\n";
}

void thread2() {
    std::lock_guard<std::mutex> lock2(mtx2);
    std::cout << "线程 2 锁定 mtx2，尝试锁定 mtx1\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));  // 模拟线程阻塞
    std::lock_guard<std::mutex> lock1(mtx1);
    std::cout << "线程 2 获取到 mtx1\n";
}

int main() {
    // 启动内存泄漏模拟
    std::thread leakThread(simulateMemoryLeak);

    // 模拟空指针访问崩溃
    std::thread nullPointerThread(simulateNullPointerAccess);

    // 启动线程死锁模拟
    std::thread t1(thread1);
    std::thread t2(thread2);

    // 等待线程执行
    leakThread.join();
    nullPointerThread.join();
    t1.join();
    t2.join();

    return 0;
}

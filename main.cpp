#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

int main() {
    std::cout << "=== 崩溃模拟器启动 ===" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    try {
        int* ptr = nullptr;
        std::cout << "访问空指针..." << std::endl;
        std::cout << *ptr << std::endl;  // 故意崩溃
    } catch (...) {
        std::cout << "捕获到异常，模拟崩溃结束。" << std::endl;
    }

    std::cout << "程序结束。" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 0;
}

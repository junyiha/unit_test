/**
 * @file test_queue.cc
 * @author your name (you@domain.com)
 * @brief 测试队列
 * @version 0.1
 * @date 2023-06-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <queue>

int main() {
    std::queue<int> myQueue;
    myQueue.push(10);
    myQueue.push(20);
    myQueue.push(30);

    if (!myQueue.empty()) {
        myQueue.pop();
        int frontElement = myQueue.front();  // 获取头部元素的值
        // 复制头部元素到另一个变量
        int copiedElement = frontElement;

        std::cout << "Front element: " << frontElement << std::endl;
        std::cout << "Copied element: " << copiedElement << std::endl;
    }

    return 0;
}

//
// Created by 15713 on 24-10-27.
//
#include <iostream>
#include <cassert>
#include "queue.h"  // Ensure this matches the location of your queue implementation

void testArrayQueue() {
    array_queue<int> q;

    // Test if the queue is empty
    assert(q.empty() == true);
    std::cout << "Test 1 passed: Initial empty state." << std::endl;

    // Push elements into the queue
    std::cout << "Pushing elements: 1, 2, 3" << std::endl;
    q.push(1);
    q.push(2);
    q.push(3);

    // Check size and front/back elements
    assert(q.size() == 3);
    assert(q.front() == 1);
    assert(q.back() == 3);
    std::cout << "Test 2 passed: Size, front, and back after pushes." << std::endl;

    // Pop an element
    std::cout << "Popping one element" << std::endl;
    q.pop();

    // Check size and front/back after popping
    assert(q.size() == 2);
    assert(q.front() == 2);
    assert(q.back() == 3);
    std::cout << "Test 3 passed: Size, front, and back after popping." << std::endl;

    // Pop remaining elements
    q.pop();
    q.pop();
    assert(q.size() == 0);
    assert(q.empty() == true);
    std::cout << "Test 4 passed: Queue is empty after popping all elements." << std::endl;

    // Test exceptions
    bool exceptionCaught = false;
    try {
        q.front();
    } catch (const std::out_of_range &e) {
        exceptionCaught = true;
    }
    assert(exceptionCaught == true);
    std::cout << "Test 5 passed: Exception caught when accessing front of empty queue." << std::endl;

    exceptionCaught = false;
    try {
        q.back();
    } catch (const std::out_of_range &e) {
        exceptionCaught = true;
    }
    assert(exceptionCaught == true);
    std::cout << "Test 6 passed: Exception caught when accessing back of empty queue." << std::endl;

    exceptionCaught = false;
    try {
        q.pop();
    } catch (const std::out_of_range &e) {
        exceptionCaught = true;
    }
    assert(exceptionCaught == true);
    std::cout << "Test 7 passed: Exception caught when popping from empty queue." << std::endl;

    // Test reallocation
    std::cout << "Pushing 10 elements to test reallocation" << std::endl;
    for (int i = 0; i < 10; ++i) {
        q.push(i);
        assert(q.size() == i + 1);
        std::cout << "Pushed: " << i << ", Size: " << q.size() << std::endl;
    }
    std::cout << "Test 8 passed: Final size, front, and back after reallocation." << std::endl;

    // 测试构造函数
    array_queue<int> q1;
    assert(q1.empty() == true);
    std::cout << "Test 1 passed: Initial empty state of q1." << std::endl;

    // 测试推入元素
    std::cout << "Pushing elements: 1, 2, 3" << std::endl;
    q1.push(1);
    q1.push(2);
    q1.push(3);
    assert(q1.size() == 3);
    assert(q1.front() == 1);
    assert(q1.back() == 3);
    std::cout << "Test 2 passed: Size, front, and back after pushes." << std::endl;

    // 测试复制构造函数
    array_queue<int> q2(q1);  // 使用复制构造函数
    assert(q2.size() == q1.size());
    assert(q2.front() == q1.front());
    assert(q2.back() == q1.back());
    std::cout << "Test 3 passed: Copy constructor works." << std::endl;

    // 测试赋值运算符重载
    array_queue<int> q3;
    q3 = q1;  // 赋值运算符
    assert(q3.size() == q1.size());
    assert(q3.front() == q1.front());
    assert(q3.back() == q1.back());
    std::cout << "Test 4 passed: Assignment operator works." << std::endl;

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    testArrayQueue();
    return 0;
}


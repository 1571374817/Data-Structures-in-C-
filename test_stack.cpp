//
// Created by 15713 on 24-10-26.
//
#include <iostream>
#include <cassert>
#include "Stack.h" // Include your stack header file

void testStack() {
    array_stack<int> stack;

    // Test 1: Check if the stack is empty
    assert(stack.empty());
    std::cout << "Test 1 passed: Stack is empty." << std::endl;

    // Test 2: Push elements onto the stack
    for (int i = 0; i < 5; ++i) {
        stack.push(i);
        assert(stack.size() == i + 1); // Verify the size after each push
        std::cout << "Pushed: " << i << ", Stack size: " << stack.size() << " (Test 2 passed)" << std::endl;
    }

    // Test 3: Check the top element
    assert(stack.top() == 4); // Last pushed element should be on top
    std::cout << "Test 3 passed: Top element is " << stack.top() << std::endl;

    // Test 4: Pop elements from the stack
    for (int i = 4; i >= 0; --i) {
        assert(stack.top() == i); // Check top before popping
        std::cout << "Popped: " << stack.top() << std::endl;
        stack.pop();
        assert(stack.size() == i); // Verify the size after each pop
        std::cout << "Stack size after pop: " << stack.size() << " (Test 4 passed)" << std::endl;
    }

    // Test 5: Try to pop from an empty stack
    try {
        stack.pop();
        assert(false); // Should not reach here
    } catch (const std::out_of_range &) {
        std::cout << "Test 5 passed: Caught exception when popping from an empty stack." << std::endl;
    }

    // Test 6: Copy constructor
    array_stack<int> copy_stack = stack; // Should be empty
    assert(copy_stack.size() == 0);
    std::cout << "Test 6 passed: Copy stack size after copying from empty stack: " << copy_stack.size() << std::endl;

    // Push elements to the original stack again
    for (int i = 10; i < 15; ++i) {
        stack.push(i);
    }

    // Test 7: Check if the copied stack remains unchanged
    assert(stack.size() == 5); // Original stack size
    assert(copy_stack.size() == 0); // Copy stack should still be empty
    std::cout << "Test 7 passed: Original stack size: " << stack.size() << ", Copy stack size: " << copy_stack.size() << std::endl;

    // Test 8: Assignment operator
    array_stack<int> assigned_stack;
    assigned_stack = stack; // Assign original stack to a new stack
    assert(assigned_stack.size() == stack.size()); // Check sizes are equal
    std::cout << "Test 8 passed: Assigned stack size after assignment: " << assigned_stack.size() << std::endl;

    // Test 9: Check top of the assigned stack
    assert(assigned_stack.top() == stack.top());
    std::cout << "Test 9 passed: Top of assigned stack is " << assigned_stack.top() << std::endl;

    // Test 10: Popping from assigned stack
    while (!assigned_stack.empty()) {
        std::cout << "Popped from assigned stack: " << assigned_stack.top() << std::endl;
        assigned_stack.pop();
    }
    assert(assigned_stack.empty());
    std::cout << "Test 10 passed: Assigned stack is empty after popping all elements." << std::endl;
}

void testLinkedStack() {
    linked_stack<int> stack;

    // Test 1: Check if the stack is empty
    assert(stack.empty());
    std::cout << "Test 1 passed: Stack is empty." << std::endl;

    // Test 2: Push elements onto the stack
    for (int i = 0; i < 5; ++i) {
        stack.push(i);
        assert(stack.size() == i + 1); // Verify the size after each push
        std::cout << "Pushed: " << i << ", Stack size: " << stack.size() << " (Test 2 passed)" << std::endl;
    }

    // Test 3: Check the top element
    assert(stack.top() == 4); // Last pushed element should be on top
    std::cout << "Test 3 passed: Top element is " << stack.top() << std::endl;

    // Test 4: Pop elements from the stack
    for (int i = 4; i >= 0; --i) {
        assert(stack.top() == i); // Check top before popping
        std::cout << "Popped: " << stack.top() << std::endl;
        stack.pop();
        assert(stack.size() == i); // Verify the size after each pop
        std::cout << "Stack size after pop: " << stack.size() << " (Test 4 passed)" << std::endl;
    }

    // Test 5: Try to pop from an empty stack
    try {
        stack.pop();
        assert(false); // Should not reach here
    } catch (const std::out_of_range &) {
        std::cout << "Test 5 passed: Caught exception when popping from an empty stack." << std::endl;
    }

    // Test 6: Copy constructor
    linked_stack<int> copy_stack = stack; // Should be empty
    assert(copy_stack.size() == 0);
    std::cout << "Test 6 passed: Copy stack size after copying from empty stack: " << copy_stack.size() << std::endl;

    // Push elements to the original stack again
    for (int i = 10; i < 15; ++i) {
        stack.push(i);
    }

    // Test 7: Check if the copied stack remains unchanged
    assert(stack.size() == 5); // Original stack size
    assert(copy_stack.size() == 0); // Copy stack should still be empty
    std::cout << "Test 7 passed: Original stack size: " << stack.size() << ", Copy stack size: " << copy_stack.size() << std::endl;

    // Test 8: Assignment operator
    linked_stack<int> assigned_stack;
    assigned_stack = stack; // Assign original stack to a new stack
    assert(assigned_stack.size() == stack.size()); // Check sizes are equal
    std::cout << "Test 8 passed: Assigned stack size after assignment: " << assigned_stack.size() << std::endl;

    // Test 9: Check top of the assigned stack
    assert(assigned_stack.top() == stack.top());
    std::cout << "Test 9 passed: Top of assigned stack is " << assigned_stack.top() << std::endl;

    // Test 10: Popping from assigned stack
    while (!assigned_stack.empty()) {
        std::cout << "Popped from assigned stack: " << assigned_stack.top() << std::endl;
        assigned_stack.pop();
    }
    assert(assigned_stack.empty());
    std::cout << "Test 10 passed: Assigned stack is empty after popping all elements." << std::endl;
}

int main() {
    std::cout << "Testing array_stack..." << std::endl;
    testStack();
    std::cout << "All tests passed!" << std::endl;
    std::cout << "Testing linked_stack..." << std::endl;
    testLinkedStack();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}

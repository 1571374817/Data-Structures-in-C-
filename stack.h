//
// Created by 15713 on 24-10-26.
//

#ifndef STACK_H
#define STACK_H
#include <stdexcept>

#include "Linear_List.h"

// 用C++实现栈

// 抽象数据类型 stack{
//     实例
//         线性表：一端为底，一端为顶
//     操作
//         empty(): // 判断栈是否为空
//         size(): // 返回栈中元素个数
//         top(): // 返回栈顶元素
//         pop(): //删除栈顶元素
//         push(x): // 将x压入栈中
// };

template<typename T>
class stack {
public:
    virtual ~stack() = default;

    // [[nodiscard]] C++17新特性
    // 对于被标记的函数若是没有使用其返回值，编译器会提出警告
    [[nodiscard]] virtual bool empty() const = 0;

    [[nodiscard]] virtual int size() const = 0;

    virtual T &top() const = 0;

    virtual void pop() = 0;

    virtual void push(const T &x) = 0;
};

// 用数组描述
template<typename T>
class array_stack : public stack<T> {
public:
    explicit array_stack(int initial_capacity = 10);

    array_stack(const array_stack<T> &);

    array_stack<T> &operator=(const array_stack<T> &);

    ~array_stack() override { delete[] stack; }

    // 栈顶指针为-1时表示栈空
    [[nodiscard]] bool empty() const override { return stack_top == -1; }

    [[nodiscard]] int size() const override { return stack_top + 1; }

    T &top() const override {
        if (stack_top == -1) {
            throw std::out_of_range("stack is empty");
        }
        return stack[stack_top];
    }

    void pop() override {
        if (stack_top == -1) {
            throw std::out_of_range("stack is empty");
        }
        stack[stack_top--].~T(); // 调用析构函数删除栈顶元素
    }

    void push(const T &x) override;

private:
    int stack_top;  // 栈顶指针
    int array_size; // 栈容量
    T *stack;       // 元素数组
};

template<typename T>
array_stack<T>::array_stack(int initial_capacity) {
    if (initial_capacity <= 0) {
        throw std::invalid_argument("initial capacity must be > 0");
    }
    array_size = initial_capacity;
    stack = new T[array_size];
    stack_top = -1;
}

template<typename T>
array_stack<T>::array_stack(const array_stack<T> &other_stack) {
    array_size = other_stack.array_size;
    stack = new T[array_size];
    stack_top = other_stack.stack_top;
    std::copy(other_stack.stack, other_stack.stack + other_stack.stack_top + 1,stack);
}

template<typename T>
array_stack<T> &array_stack<T>::operator=(const array_stack<T> &other_stack) {
    if(this != &other_stack) {
        delete[] stack;
        array_size = other_stack.array_size;
        stack = new T[array_size];
        stack_top = other_stack.stack_top;
        std::copy(other_stack.stack, other_stack.stack + other_stack.stack_top + 1, stack);
    }
    return *this;
}

template<typename T>
void array_stack<T>::push(const T &x) {
    // 空间已满，容量加倍
    if (stack_top == array_size - 1) {
        int new_array_size = array_size * 2;
        T *new_array_stack = new T[new_array_size];
        std::copy(stack, stack + stack_top + 1, new_array_stack);
        delete[] stack;
        stack = new_array_stack;
        array_size = new_array_size;
    }
    stack[++stack_top] = x; // 在栈顶插入
}

#endif //STACK_H

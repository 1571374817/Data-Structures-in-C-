//
// Created by 15713 on 24-10-26.
//

#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>

// 队列

// 抽象数据类型 queue{
//     实例
//         元素的有序表，一端为队首，一端为队尾
//     操作
//         empty(): // 判断队列是否为空
//         size(): // 队列中元素个数
//         front(): // 队首元素
//         back(): // 队尾元素
//         pop(): // 删除队列首元素
//         push(x): // 把x加到队尾
// }

template<typename T>
class queue {
public:
    virtual ~queue() = default;

    [[nodiscard]] virtual bool empty() const = 0;

    [[nodiscard]] virtual int size() const = 0;

    virtual T &front() = 0;

    virtual T &back() = 0;

    virtual void pop() = 0;

    virtual void push(const T &element) = 0;
};

// 用数组描述
// 队列元素位置为queue(i) = (queue + i) % array_queue_capacity
// 为了区别判空和判满，队列首元素指针queue_front不存放元素
// 当插入元素到队列中，若队列插满，则需要扩容保证queue_front不存放元素
template<typename T>
class array_queue : public queue<T> {
public:
    explicit array_queue(int initial_capacity = 10);

    array_queue(const array_queue &other_queue);

    array_queue &operator=(const array_queue &other_queue);

    ~array_queue() override { delete[] queue; }

    [[nodiscard]] bool empty() const override { return queue_front == queue_back; }

    [[nodiscard]] int size() const override {
        return (queue_back - queue_front + array_queue_capacity) % array_queue_capacity;
    }

    T &front() override {
        if (queue_front == queue_back) {
            throw std::out_of_range("queue is empty");
        }
        return queue[queue_front + 1];
    }

    T &back() override {
        if (queue_front == queue_back) {
            throw std::out_of_range("queue is empty");
        }
        return queue[queue_back];
    }

    void pop() override;

    void push(const T &element) override;

private:
    int array_queue_capacity; // 队列容量
    T *queue;                 // 队列
    int queue_front;          // 队列首元素索引
    int queue_back;           // 队尾元素索引
};

template<typename T>
array_queue<T>::array_queue(int initial_capacity) {
    if (initial_capacity <= 0) {
        throw std::invalid_argument("initial capacity must be greater than zero");
    }
    array_queue_capacity = initial_capacity;
    queue = new T[array_queue_capacity];
    queue_front = 0;
    queue_back = 0;
}

template<typename T>
array_queue<T>::array_queue(const array_queue &other_queue) {
    array_queue_capacity = other_queue.array_queue_capacity;
    queue = new T[array_queue_capacity];
    queue_front = other_queue.queue_front;
    queue_back = other_queue.queue_back;
    // 处理环绕情况
    if (other_queue.queue_front < other_queue.queue_back) {
        std::copy(other_queue.queue + other_queue.queue_front + 1,
                  other_queue.queue + other_queue.queue_back + 1,
                  queue + queue_front + 1);
    } else {
        std::copy(other_queue.queue + other_queue.queue_front + 1,
                  other_queue.queue + array_queue_capacity,
                  queue + queue_front + 1);
        std::copy(other_queue.queue,
                  other_queue.queue + other_queue.queue_back + 1,
                  queue);
    }
}

template<typename T>
array_queue<T> &array_queue<T>::operator=(const array_queue &other_queue) {
    if (this != &other_queue) {
        delete[] queue;
        array_queue_capacity = other_queue.array_queue_capacity;
        queue = new T[array_queue_capacity];
        queue_front = other_queue.queue_front;
        queue_back = other_queue.queue_back;
        // 处理环绕情况
        if (other_queue.queue_front < other_queue.queue_back) {
            std::copy(other_queue.queue + other_queue.queue_front + 1,
                      other_queue.queue + other_queue.queue_back + 1,
                      queue + queue_front + 1);
        } else {
            std::copy(other_queue.queue + other_queue.queue_front + 1,
                      other_queue.queue + array_queue_capacity,
                      queue + queue_front + 1);
            std::copy(other_queue.queue,
                      other_queue.queue + other_queue.queue_back + 1,
                      queue);
        }
    }
    return *this;
}

template<typename T>
void array_queue<T>::pop() {
    if (queue_front == queue_back) {
        throw std::out_of_range("queue is empty");
    }
    queue_front = (queue_front + 1) % array_queue_capacity;
    queue[queue_front].~T();
}

template<typename T>
void array_queue<T>::push(const T &element) {
    // 检查队列是否已满
    if ((queue_back + 1) % array_queue_capacity == queue_front) {
        T *new_queue = new T[2 * array_queue_capacity];

        // 复制元素到新数组
        int start = (queue_front + 1) % array_queue_capacity;
        if (queue_back >= queue_front) {
            // 没有环绕，直接复制
            std::copy(queue + start, queue + queue_back + 1, new_queue);
        } else {
            // 有环绕，分两部分复制
            std::copy(queue + start, queue + array_queue_capacity, new_queue);
            std::copy(queue, queue + queue_back + 1, new_queue + (array_queue_capacity - start));
        }
        // 更新 front 和 back
        queue_front = 2 * array_queue_capacity - 1; // 根据新数组调整
        queue_back = array_queue_capacity - 2; // 更新为复制的元素个数
        array_queue_capacity *= 2;
        delete[] queue; // 释放旧数组
        queue = new_queue; // 更新为新数组
    }
    // 在队尾插入新元素
    queue_back = (queue_back + 1) % array_queue_capacity;
    queue[queue_back] = element;
}

#endif //QUEUE_H

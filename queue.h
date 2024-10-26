//
// Created by 15713 on 24-10-26.
//

#ifndef QUEUE_H
#define QUEUE_H

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
#endif //QUEUE_H

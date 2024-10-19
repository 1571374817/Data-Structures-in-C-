//
// Created by 15713 on 24-10-18.
//

#ifndef LINEAR_LIST_H
#define LINEAR_LIST_H

#include <algorithm>
#include <iostream>

// 一个抽象类实现线性表的抽象数据类型 (abstract data type, ADT)
// 抽象数据类型linear_List {
//     实例
//         有限个元素的有序集合
//     操作
//         is_empty():判断线性表是否为空
//         size():返回线性表中元素个数
//         get(index):返回索引为 index 的元素
//         indexOf(x):返回元素 x 的索引
//         erase(index):删除索引为 index 的元素
//         insert(index,x):在索引为 index 的位置插入元素 x
//         output():从左到右输出元素
// }

template<typename T>
class Linear_List {
public:
    virtual ~Linear_List() = default;

    // [[nodiscard]] C++17新特性
    // 对于被标记的函数若是没有使用其返回值，编译器会提出警告
    [[nodiscard]] virtual bool is_empty() const = 0;

    [[nodiscard]] virtual int size() const = 0;

    virtual T &get(int index) const = 0;

    virtual int indexOf(const T &value) const = 0;

    virtual void erase(int index) = 0;

    virtual void insert(int index, const T &value) = 0;

    virtual void output() const = 0;
};

// 用数组描述线性表
template<typename T>
class array_List : public Linear_List<T> {
public:
    // 构造函数、拷贝构造函数、析构函数
    explicit array_List(int initial_capacity);

    array_List(const array_List<T> &other_List);

    ~array_List() override { delete[] elements; };// 不能使用默认析构函数

    // ADT(abstract data type) 方法
    [[nodiscard]] bool is_empty() const override { return list_size == 0; }

    [[nodiscard]] int size() const override { return list_size; }

    T &get(int index) const override;

    int indexOf(const T &value) const override;

    void erase(int index) override;

    void insert(int index, const T &value) override;

    void output() const override;

private:
    // 若索引 index 无效，抛出异常
    void check_index(int index) const;

    T *elements;      // 存储线性表的一维数组
    int array_capacity; // 一维数组的容量
    int list_size;    // 线性表的元素个数
};

// 构造函数
template<typename T>
array_List<T>::array_List(int initial_capacity) {
    // 数组初始长度不能为0
    if(initial_capacity < 1) {
        throw std::invalid_argument("initial_capacity must be greater than 0.");
    }
    array_capacity = initial_capacity;
    elements = new T[array_capacity];
    list_size = 0;
}

// 拷贝构造函数
template<typename T>
array_List<T>::array_List(const array_List<T> &other_List) {
    array_capacity = other_List.array_capacity;
    list_size = other_List.list_size;
    elements = new T[array_capacity];
    std::copy(other_List.elements, other_List.elements + list_size, elements);
}

// check_index
template<typename T>
void array_List<T>::check_index(int index) const {
    // 保证 index 在 0-list_size-1之间
    if(index < 0 || index >= list_size) {
        throw std::invalid_argument("index out of range.");
    }
}

// get
template<typename T>
T &array_List<T>::get(int index) const {
    check_index(index);
    return elements[index];
}

// indexOf
template<typename T>
int array_List<T>::indexOf(const T &value) const {
    int index = 0;
    for(; index < list_size; ++index) {
        if(elements[index] == value) {
            break;
        }
    }
    // 没有找到，返回 -1
    if(index == list_size) {
        return -1;
    }
    return index;
}

// erase
template<typename T>
void array_List<T>::erase(int index) {
    check_index(index);
    for(int i = index; i < list_size - 1; ++i) {
        elements[i] = elements[i + 1];
    }
    // 删除一个元素，list_size - 1
    // 需要删除最后一个元素
    elements[--list_size].~T();
}

// insert
template<typename T>
void array_List<T>::insert(int index, const T &value) {
    // 无效索引，抛出异常
    // 允许在最后一个位置插入
    if(index < 0 || index > list_size) {
        throw std::invalid_argument("index out of range.");
    }
    // 有效索引，确定数组是否已满
    if(list_size == array_capacity) {
        int new_array_capacity = array_capacity * 2;
        T *new_elements = new T[new_array_capacity];
        std::copy(elements, elements + list_size, new_elements);
        delete[] elements;
        elements = new_elements;
        array_capacity = new_array_capacity;
    }
    for(int i = list_size; i > index; --i) {
        elements[i] = elements[i - 1];
    }
    elements[index] = value;
    ++list_size;
}

// output
template<typename T>
void array_List<T>::output() const {
    for(int i = 0; i < list_size; ++i) {
        std::cout << elements[i] << " ";
    }
}

#endif //LINEAR_LIST_H

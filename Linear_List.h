//
// Created by 15713 on 24-10-18.
//

#ifndef LINEAR_LIST_H
#define LINEAR_LIST_H

#include <algorithm>
#include <iostream>
#include <ranges>

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

/***************************************************************************************************/
/************************************* 用数组描述线性表***********************************************/
template<typename T>
class array_List : public Linear_List<T> {
public:
    // 构造函数、拷贝构造函数、析构函数
    explicit array_List(int initial_capacity = 10);

    array_List(const array_List<T> &other_List);

    ~array_List() override { delete[] elements; }; // 不能使用默认析构函数

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

    T *elements;        // 存储线性表的一维数组
    int array_capacity; // 一维数组的容量
    int list_size;      // 线性表的元素个数
};

// 构造函数
template<typename T>
array_List<T>::array_List(int initial_capacity) {
    // 数组初始长度不能为0
    if (initial_capacity < 1) {
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
    if (index < 0 || index >= list_size) {
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
    for (; index < list_size; ++index) {
        if (elements[index] == value) {
            break;
        }
    }
    // 没有找到，返回 -1
    if (index == list_size) {
        return -1;
    }
    return index;
}

// erase
template<typename T>
void array_List<T>::erase(int index) {
    if (list_size == 0) {
        return;
    }
    check_index(index);
    for (int i = index; i < list_size - 1; ++i) {
        elements[i] = elements[i + 1];
    }
    // 删除一个元素，list_size - 1
    // 需要删除最后一个元素
    elements[--list_size].~T();
    // 当线性表元素减少到 list_size < array_capacity / 4
    // 将数组长度减少到 max{initial_capacity,array_capacity}
    if (list_size < array_capacity / 4) {
        int new_array_capacity = std::max(10, array_capacity / 2);
        T *new_elements = new T[new_array_capacity];
        std::copy(elements, elements + list_size, new_elements);
        delete[] elements;
        elements = new_elements;
    }
}

// insert
template<typename T>
void array_List<T>::insert(int index, const T &value) {
    // 无效索引，抛出异常
    // 允许在最后一个位置插入
    if (index < 0 || index > list_size) {
        throw std::invalid_argument("index out of range.");
    }
    // 有效索引，确定数组是否已满
    if (list_size == array_capacity) {
        int new_array_capacity = array_capacity * 2;
        T *new_elements = new T[new_array_capacity];
        std::copy(elements, elements + list_size, new_elements);
        delete[] elements;
        elements = new_elements;
        array_capacity = new_array_capacity;
    }
    for (int i = list_size; i > index; --i) {
        elements[i] = elements[i - 1];
    }
    elements[index] = value;
    ++list_size;
}

// output
template<typename T>
void array_List<T>::output() const {
    for (int i = 0; i < list_size; ++i) {
        std::cout << elements[i] << " ";
    }
}

/***********************************************************************************************/
/***********************************用链表描述线性表*********************************************/
// 链表节点
template<typename T>
struct chain_Node {
    T element;
    chain_Node<T> *next;

    //方法
    chain_Node() = default;

    explicit chain_Node(const T &element) {
        this->element = element;
        this->next = nullptr;
    }

    chain_Node(const T &element, chain_Node<T> *next) {
        this->element = element;
        this->next = next;
    }
};

// 以下实现的方法是不含头节点的单向链表
template<typename T>
class chain_List : public Linear_List<T> {
public:
    // 构造函数、拷贝构造函数、析构函数
    explicit chain_List(int initial_capacity = 10);

    chain_List(const chain_List<T> &other_List);

    ~chain_List() override;

    // ADT
    [[nodiscard]] bool is_empty() const override { return list_size == 0; }
    [[nodiscard]] int size() const override { return list_size; }

    T &get(int index) const override;

    int indexOf(const T &value) const override;

    void erase(int index) override;

    void insert(int index, const T &value) override;

    void output() const override;

private:
    void check_index(int index) const;

    chain_Node<T> *first_Node; // 指向链表第一个节点的指针
    int list_size;             // 线性表元素个数
};

// 构造函数
template<typename T>
chain_List<T>::chain_List(int initial_capacity) {
    if (initial_capacity < 1) {
        throw std::invalid_argument("initial_capacity must be greater than 0.");
    }
    first_Node = nullptr;
    list_size = 0;
}

// 拷贝构造函数
template<typename T>
chain_List<T>::chain_List(const chain_List<T> &other_List) {
    list_size = other_List.list_size;
    if(list_size == 0) {
        first_Node = nullptr;
        return;
    }
    // 要复制链表 other_List 的节点
    chain_Node<T> *source_Node = other_List.first_Node;
    // 赋值链表 other_List 的首节点
    first_Node = new chain_Node<T>(source_Node->element);
    source_Node = source_Node->next;
    // 当前链表 *this 的最后一个节点
    chain_Node<T> *target_Node = first_Node;

    // 复制剩余元素
    while (source_Node != nullptr) {
        target_Node->next = new chain_Node<T>(source_Node->element);
        target_Node = target_Node->next;
        source_Node = source_Node->next;
    }
    target_Node->next = nullptr; // 链表结束
}

// 析构函数
template<typename T>
chain_List<T>::~chain_List() {
    // 删除链表的所有节点
    while(first_Node != nullptr) {
        chain_Node<T> *temp = first_Node->next;
        delete first_Node;
        first_Node = temp;
    }
}

// check_index
template<typename T>
void chain_List<T>::check_index(int index) const {
    if (index < 0 || index >= list_size) {
        throw std::invalid_argument("index out of range.");
    }
}

// get
template<typename T>
T &chain_List<T>::get(int index) const {
    check_index(index);

    // 移向需要返回的节点
    chain_Node<T> *current_Node = first_Node;
    for(int i = 0; i < index; ++i) {
        current_Node = current_Node->next;
    }
    return current_Node->element;
}

// indexOf
template<typename T>
int chain_List<T>::indexOf(const T &value) const {
    int index = 0;
    chain_Node<T> *current_Node = first_Node;
    while (current_Node != nullptr) {
        if (current_Node->element == value) {
            break;
        }
        current_Node = current_Node->next;
        ++index;
    }
    // 没找到，返回 -1
    if(current_Node == nullptr) {
        return -1;
    }
    return index;
}

// erase
template<typename T>
void chain_List<T>::erase(int index) {
    if (list_size == 0) {
        return;
    }
    check_index(index);
    // 要删除的节点
    chain_Node<T> *delete_Node;
    // 删除第一个节点
    if(index == 0) {
        delete_Node = first_Node;
        first_Node = first_Node->next;
    }else {
        // 删除其他位置
        chain_Node<T> *previous_Node = first_Node; // 要删除节点的前驱节点
        for(int i = 1; i < index - 1; ++i) {
            previous_Node = previous_Node->next;
        }
        delete_Node = previous_Node->next;
        previous_Node->next = previous_Node->next->next;
    }
    --list_size;
    delete delete_Node;
}

// insert
template<typename T>
void chain_List<T>::insert(int index, const T &value) {
    // 无效索引
    if(index < 0 || index > list_size) {
        throw std::invalid_argument("index out of range.");
    }
    // 在第一个位置插入
    if(index == 0) {
        first_Node = new chain_Node<T>(value, first_Node);
    }else {
        // 在其他位置插入
        // 找到要插入位置的前驱
        chain_Node<T> *previous_Node = first_Node;
        for(int i = 0; i < index - 1; ++i) {
            previous_Node = previous_Node->next;
        }
        previous_Node->next = new chain_Node<T>(value, previous_Node->next);
    }
    ++list_size;
}

// output
template<typename T>
void chain_List<T>::output() const {
    chain_Node<T> *current_Node = first_Node;
    while(current_Node != nullptr) {
        std::cout << current_Node->element << " ";
        current_Node = current_Node->next;
    }
}

#endif //LINEAR_LIST_H

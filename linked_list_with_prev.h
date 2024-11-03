//
// Created by 15713 on 24-11-2.
//

#ifndef LINKED_LIST_WITH_PREV_H
#define LINKED_LIST_WITH_PREV_H

#include <iostream>
#include <stdexcept>

#include "Linear_List.h"

template<typename T>
struct list_node {
    T data;
    list_node<T> *next;
    list_node<T> *prev;

    //方法
    list_node() {
        next = nullptr;
        prev = nullptr;
    }

    explicit list_node(const T &_data) {
        data = _data;
        next = nullptr;
        prev = nullptr;
    }

    list_node(const T &_data, list_node<T> *next) {
        data = _data;
        this->next = next;
        this->prev = nullptr;
    }

    list_node(const T &_data, list_node<T> *next, list_node<T> *prev) {
        data = _data;
        this->next = next;
        this->prev = prev;
    }

    list_node(const T &_data, list_node<T> *prev, int) {
        data = _data;
        this->next = nullptr;
        this->prev = prev;
    }
};

template<typename T>
class linked_list_with_prev : public Linear_List<T> {
public:
    linked_list_with_prev() {
        this->head = nullptr;
        this->tail = nullptr;
        list_count = 0;
    }

    ~linked_list_with_prev() override;

    // ADT
    [[nodiscard]] bool is_empty() const override { return list_count == 0; }
    [[nodiscard]] int size() const override { return list_count; }

    T &get(int index) const override;

    int indexOf(const T &value) const override;

    void erase(int index) override;

    void insert(int index, const T &value) override;

    void output() const override;

    list_node<T> *get_head() const {
        return head;
    }

    list_node<T> *get_tail() const {
        return tail;
    }

    void add_Node_prev(const T &value);

    void add_Node_next(const T &value);

    list_node<T> *go_to_next(list_node<T> *node);

    list_node<T> *go_to_prev(list_node<T> *node);

private:
    void check_index(int index) const;

    list_node<T> *head;      // 链表头指针
    list_node<T> *tail;      // 链表尾指针
    unsigned int list_count; // 链表节点数量
};

template<typename T>
linked_list_with_prev<T>::~linked_list_with_prev() {
    while (head != nullptr) {
        list_node<T> *temp = head->next;
        delete head;
        head = temp;
    }
    tail = nullptr;
}

template<typename T>
void linked_list_with_prev<T>::check_index(int index) const {
    if (index >= list_count || index < 0) {
        throw std::out_of_range("index out of range");
    }
}

template<typename T>
T &linked_list_with_prev<T>::get(int index) const {
    check_index(index);
    list_node<T> *curr = head;
    for (int i = 0; i < index; ++i) {
        curr = curr->next;
    }
    return curr->data;
}

template<typename T>
void linked_list_with_prev<T>::erase(int index) {
    if(list_count == 0) {
        return;
    }
    check_index(index);
    list_node<T> *del;
    if(list_count == 1) {
        if(index != 0) {
            throw std::out_of_range("index out of range");
        }
        del = head;
        head = nullptr;
        tail = nullptr;
    }else if(index == 0) {
        del = head;
        head = head->next;
        head->prev = nullptr;
    }else if(index == list_count - 1) {
        del = tail;
        tail = tail->prev;
        tail->next = nullptr;
    }else {
        list_node<T> *prev = head;
        for (int i = 0; i < index - 1; ++i) {
            prev = prev->next;
        }
        del = prev->next;
        prev->next = del->next;
        del->next->prev = prev;
    }
    --list_count;
    delete del;
}

template<typename T>
int linked_list_with_prev<T>::indexOf(const T &value) const {
    list_node<T> *curr = head;
    int index = 0;
    while(curr != nullptr) {
        if (curr->data == value) {
            break;
        }
        curr = curr->next;
        ++index;
    }
    if(curr == nullptr) {
        return -1;
    }
    return index;
}

template<typename T>
void linked_list_with_prev<T>::insert(int index, const T &value) {
    if(index > list_count || index < 0) {
        throw std::out_of_range("index out of range");
    }
    if(index == 0) {
        head = new list_node<T>(value,head);
    }else if(index == list_count - 1) {
        tail = new list_node<T>(value,tail,0);
    }else {
        list_node<T> *prev = head;
        for (int i = 0; i < index - 1; ++i) {
            prev = prev->next;
        }
        auto *next = prev->next;
        auto *curr = new list_node<T>(value,next,prev);
        prev->next = curr;
        next->prev = curr;
    }
    ++list_count;
}

template<typename T>
void linked_list_with_prev<T>::output() const {
    list_node<T> *curr = head;
    while (curr != nullptr) {
        std::cout << curr->data << " ";
    }
}

template<typename T>
list_node<T> *linked_list_with_prev<T>::go_to_next( list_node<T> *node) {
    return node->next;
}

template<typename T>
list_node<T> *linked_list_with_prev<T>::go_to_prev(list_node<T> *node) {
    return node->prev;
}

template<typename T>
void linked_list_with_prev<T>::add_Node_prev(const T &value) {
    if(head == nullptr) {
        head = new list_node<T>(value,head);
        tail = head;
    }else {
        auto *curr = new list_node<T>(value,head);
        head->prev = curr;
        head = curr;
    }
    ++list_count;
}

template<typename T>
void linked_list_with_prev<T>::add_Node_next(const T &value) {
    if(head == nullptr) {
        tail = new list_node<T>(value,tail,0);
        head = tail;
    }else {
        auto *curr = new list_node<T>(value,tail,0);
        tail->next = curr;
        tail = curr;
    }
    ++list_count;
}

#endif //LINKED_LIST_WITH_PREV_H


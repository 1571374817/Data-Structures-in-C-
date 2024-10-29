//
// Created by 15713 on 24-10-29.
//

#ifndef LINKED_LIST_ALGORITHMS_H
#define LINKED_LIST_ALGORITHMS_H

#include "Linear_List.h"

// 反转链表
// 迭代法
template<typename T>
void reverse_List(chain_List<T> &linked_list) {
    chain_Node<T> *prev = nullptr;
    chain_Node<T> *curr = linked_list.get_first_Node();
    while (curr != nullptr) {
        chain_Node<T> *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    linked_list.set_first_Node(prev);
}

//辅助递归函数
template<typename T>
chain_Node<T> *reverse_recursive(chain_Node<T> *node) {
    // 递归基准
    if(node == nullptr || node->next == nullptr) {
        return node;
    }
    chain_Node<T> *new_node = reverse_recursive(node->next);
    node->next->next = node;
    node->next = nullptr;
    return new_node;
}
// 递归
template<typename T>
void reverse_List_Recursive(chain_List<T> &linked_list) {
    chain_Node<T> *first_Node = linked_list.get_first_Node();
    if(first_Node == nullptr || first_Node->next == nullptr) {
        return;
    }
    chain_Node<T> *new_first_node = reverse_recursive(first_Node);
    linked_list.set_first_Node(new_first_node);
}
#endif //LINKED_LIST_ALGORITHMS_H

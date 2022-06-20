//
// Created by Lenovo on 2022/4/12.
//

#ifndef C_C___LINKED_QUEUE_H
#define C_C___LINKED_QUEUE_H

#endif //C_C___LINKED_QUEUE_H
#include "global.h"

namespace linked_queue{

// 链队节点定义
T struct queue_node {
    TYPE data; // 节点数据域
    queue_node *next_node; // 节点指针域
};

// 获取节点数据域的值
T TYPE node_get_val(queue_node<TYPE> *node) {
    return node->data;
}

// 获取节点指针域的地址
T queue_node<TYPE> *node_get_next(queue_node<TYPE> *node) {
    return node->next_node;
}

// 打印节点
T void node_print(queue_node<TYPE> *node) {
    std::cout << "(" << node_get_val(node) << ", #" << node_get_next(node) << ")";
}

// 设置节点数据域的值
T void node_set_val(queue_node<TYPE> *node, TYPE val) {
    node->data = val;
}

// 设置节点指针域的地址
T void node_set_next(queue_node<TYPE> *node, queue_node<TYPE> *next) {
    node->next_node = next;
}


// 节点初始化
T queue_node<TYPE> *queue_node_init(TYPE data) {
    queue_node<TYPE> *node = (queue_node<TYPE> *) malloc(sizeof(queue_node<TYPE>));
    node_set_val(node, data);
    node_set_next(node, (queue_node<TYPE> *) nullptr);
    return node;
}

// 链队定义
T
struct linked_queue {
    queue_node<TYPE> body_pointer; // 链队哨兵节点
    queue_node<TYPE> *tail; // 链队队尾指针
    int cnt;
};

// 链栈初始化
T linked_queue<TYPE> *queue_init() {
    linked_queue<TYPE> *queue = (linked_queue<TYPE> *) malloc(sizeof(linked_queue<TYPE>));
    TYPE* e = (TYPE*)malloc(sizeof(TYPE));
    queue->body_pointer = *queue_node_init<TYPE>(*e);
    queue->tail = &queue->body_pointer;
    queue->cnt = 0;
    return queue;
}

// 返回链队长度
T int queue_length(linked_queue<TYPE> *queue) {
    return queue->cnt;
}

// 检查链队是否为空
T bool queue_check_empty(linked_queue<TYPE> *queue) {
    return !queue_length(queue);
}

// 打印链队
T void queue_print(linked_queue<TYPE> *queue) {
    std::cout << "[";
    queue_node<TYPE> *pointer = node_get_next(&queue->body_pointer);
    if (queue_length(queue)) {
        for (int i = 0; i < queue_length(queue) - 1; ++i) {
            node_print(pointer);
            pointer = node_get_next(pointer);
            std::cout << "<-";
        }
        node_print(pointer);
    }
    std::cout << "]";
}

// 获取队头节点
T queue_node<TYPE> *queue_get_front(linked_queue<TYPE> *queue) {
    if (queue_check_empty(queue)) {
        ILLEGAL_INDEX;
    }
    return node_get_next(&queue->body_pointer);
}

// 获取队尾节点
T queue_node<TYPE> *queue_get_tail(linked_queue<TYPE> *queue) {
    if (queue_check_empty(queue)) {
        ILLEGAL_INDEX;
    }
    return queue->tail;
}

// 将节点入队至队尾
T void queue_push_(linked_queue<TYPE> *queue, queue_node<TYPE> *node) {
    node_set_next(queue->tail, node);
    queue->tail = node;
    queue->cnt += 1;
}

// 将元素入队（自动装箱）
T void queue_push(linked_queue<TYPE> *queue, TYPE elem){
    queue_push_(queue, queue_node_init(elem));
}

// 将节点从队头出队并返回
T queue_node<TYPE> *queue_pop_(linked_queue<TYPE> *queue) {
    if (queue_check_empty(queue)) {
        POP_ERROR;
    }
    queue_node<TYPE> *node = node_get_next(&queue->body_pointer);
    if (node == queue->tail) {
        queue->tail = &queue->body_pointer;
    }
    node_set_next(&queue->body_pointer, node_get_next(node));
    node_set_next(node, (queue_node<TYPE> *) nullptr);
    queue->cnt -= 1;
    return node;
}

// 将元素出队（自动拆箱）
T TYPE queue_pop(linked_queue<TYPE> *queue){
    return queue_pop_(queue)->data;
}

}
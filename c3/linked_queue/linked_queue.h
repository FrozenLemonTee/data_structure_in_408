//
// Created by Lenovo on 2022/4/12.
//

#ifndef C_C___LINKED_QUEUE_H
#define C_C___LINKED_QUEUE_H

#endif //C_C___LINKED_QUEUE_H
#include "global.h"

// 链队节点定义
typedef struct queue_node{
    int data; // 节点数据域
    queue_node* next_node; // 节点指针域
}queue_node;

// 获取节点数据域的值
int node_get_val(queue_node* node){
    return node->data;
}

// 获取节点指针域的地址
queue_node* node_get_next(queue_node* node){
    return node->next_node;
}

// 打印节点
void node_print(queue_node* node){
    std::cout << "(" << node_get_val(node) << ", #" << node_get_next(node) << ")";
}

// 设置节点数据域的值
void node_set_val(queue_node* node, int val){
    node->data = val;
}

// 设置节点指针域的地址
void node_set_next(queue_node* node, queue_node* next){
    node->next_node = next;
}


// 节点初始化
queue_node* node_init(int data){
    queue_node* node = (queue_node*)malloc(sizeof(queue_node));
    node_set_val(node, data);
    node_set_next(node, NULL);
    return node;
}

// 链队定义
typedef struct linked_queue{
    queue_node body_pointer; // 链队哨兵节点
    queue_node* tail; // 链队队尾指针
    int cnt;
}linked_queue;

// 链栈初始化
linked_queue* queue_init(){
    linked_queue* queue = (linked_queue*)malloc(sizeof(linked_queue));
    queue->body_pointer = *node_init(INT_MAX);
    queue->tail = &queue->body_pointer;
    queue->cnt = 0;
    return queue;
}

// 返回链队长度
int queue_length(linked_queue* queue){
    return queue->cnt;
}

// 检查链队是否为空
bool queue_check_empty(linked_queue* queue){
    return !queue_length(queue);
}

// 打印链队
void queue_print(linked_queue* queue){
    std::cout << "[";
    queue_node* pointer = node_get_next(&queue->body_pointer);
    if (queue_length(queue)){
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
queue_node* queue_get_front(linked_queue* queue){
    if (queue_check_empty(queue)){
        ILLEGAL_INDEX;
    }
    return node_get_next(&queue->body_pointer);
}

// 获取队尾节点
queue_node* queue_get_tail(linked_queue* queue){
    if (queue_check_empty(queue)){
        ILLEGAL_INDEX;
    }
    return queue->tail;
}

// 将节点入队至队尾
void queue_push(linked_queue* queue, queue_node* node){
    node_set_next(queue->tail, node);
    queue->tail = node;
    queue->cnt += 1;
}

// 将节点从队头出队并返回
queue_node* queue_pop(linked_queue* queue){
    if (queue_check_empty(queue)){
        POP_ERROR;
    }
    queue_node* node = node_get_next(&queue->body_pointer);
    if (node == queue->tail){
        queue->tail = &queue->body_pointer;
    }
    node_set_next(&queue->body_pointer, node_get_next(node));
    node_set_next(node, NULL);
    queue->cnt -= 1;
    return node;
}
//
// Created by Lenovo on 2022/4/11.
//

#ifndef C_C___CIRCULAR_QUEUE_H
#define C_C___CIRCULAR_QUEUE_H

#endif //C_C___CIRCULAR_QUEUE_H
#include "global.h"

// 循环队列定义
typedef struct circular_queue {
    int* queue_body; // 指向队列本体的指针
    int max_size; // 队列本体最大长度
    int front; // 队头指针
    int tail; // 队尾指针
}circular_queue;

// 循环队列初始化
circular_queue* queue_init(int max_size){
    circular_queue* queue = (circular_queue*)malloc(sizeof(circular_queue));
    queue->queue_body = (int*)malloc(sizeof(int) * max_size);
    queue->max_size = max_size;
    queue->front = 0;
    queue->tail = 0;
    return queue;
}

// 返回队列的当前长度
int queue_length(circular_queue* queue){
    return (queue->tail - queue->front + queue->max_size) % queue->max_size;
}

// 判断队列是否为空
bool queue_empty_check(circular_queue* queue){
    return queue->front == queue->tail;
}

// 判断队列是否达到最大长度
bool queue_max_size_check(circular_queue* queue){
    return (queue->tail + 1) % queue->max_size == queue->front;
}

// 获取队头元素
int queue_get_front(circular_queue* queue){
    if (queue_empty_check(queue)){
        ILLEGAL_INDEX;
    }
    return queue->queue_body[queue->front];
}

// 获取队尾元素
int queue_get_tail(circular_queue* queue){
    if (queue_empty_check(queue)){
        ILLEGAL_INDEX;
    }
    return queue->queue_body[(queue->tail - 1) % queue->max_size];
}

// 将元素入队至队尾
void queue_push(circular_queue* queue, int val){
    if (queue_max_size_check(queue)){
        INSERT_ERROR;
    }
    queue->queue_body[queue->tail] = val;
    queue->tail = (queue->tail + 1) % queue->max_size;
}

// 将元素从队头出队并返回
int queue_pop(circular_queue* queue){
    if (queue_empty_check(queue)){
        POP_ERROR;
    }
    int val = queue->queue_body[queue->front];
    queue->front = (queue->front + 1) % queue->max_size;
    return val;
}

// 打印整个队列
void queue_print(circular_queue* queue){
    std::cout << "[";
    for (int i = 0, pointer = queue->front; i < queue_length(queue); ++i, pointer = (pointer + 1) % queue->max_size){
        std::cout << queue->queue_body[pointer] << ",";
    }
    std::cout << "]";
}
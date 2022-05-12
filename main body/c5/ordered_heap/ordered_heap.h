//
// Created by Lenovo on 2022/5/11.
//

#ifndef C_C___ORDERED_HEAP_H
#define C_C___ORDERED_HEAP_H

#endif //C_C___ORDERED_HEAP_H
#include "global.h"

T struct ordered_heap;
T void heap_down(ordered_heap<TYPE>* heap, int order);

// 顺序堆类型
#define MIN_HEAP false
#define MAX_HEAP true

// 顺序堆定义
T struct ordered_heap{
    bool type; // 0时为小根堆，1时为大根堆
    int max_size; // 顺序堆最大存储空间
    int size; // 当前堆元素个数
    TYPE* data; // 顺序堆数据区域
};

// 检查序号是否合法
T bool heap_check_order(ordered_heap<TYPE>* heap, int order){
    return order > 0 && order <= heap->size;
}

// 检查堆中元素个数是否达到最大个数
T bool heap_check_full(ordered_heap<TYPE>* heap){
    return heap->size == heap->max_size;
}

// 检查堆是否为空
T bool heap_check_empty(ordered_heap<TYPE>* heap){
    return !heap->size;
}

// 通过序号访问元素
T TYPE heap_get_elem(ordered_heap<TYPE>* heap, int order){
    if (!heap_check_order(heap, order)){
        ILLEGAL_SUFFIX;
    }
    return heap->data[order - 1];
}

// 获取堆顶元素
T TYPE heap_get_top(ordered_heap<TYPE>* heap){
    return heap_get_elem(heap, 1);
}

// 获取左孩子节点序号
int get_left(int parent){
    return parent * 2;
}

// 获取右孩子节点序号
int get_right(int parent){
    return parent * 2 + 1;
}

// 获取至亲节点序号
int get_parent(int child){
    return child / 2;
}

// 检查前者元素是否比后者元素优先级高
T bool higher_priority(ordered_heap<TYPE>* heap, int order1, int order2){
    if (!heap->type){
        return heap_get_elem(heap, order1) < heap_get_elem(heap, order2);
    }
    return heap_get_elem(heap, order1) > heap_get_elem(heap, order2);
}

// 获取优先级更高的孩子结点序号
T int get_prior_child(ordered_heap<TYPE>* heap, int order){
    if (heap_check_order(heap, get_right(order))){
        return higher_priority(heap, get_left(order), get_right(order)) ? get_left(order) : get_right(order);
    }
    return get_left(order);
}

// 堆初始化
T ordered_heap<TYPE>* heap_init(bool type, int max_size){
    ordered_heap<TYPE>* heap = (ordered_heap<TYPE>*)malloc(sizeof(ordered_heap<TYPE>));
    heap->type = type;
    heap->max_size = max_size;
    heap->size = 0;
    heap->data = (TYPE*)malloc(sizeof(TYPE) * max_size);
    return heap;
}

// 堆初始化
T ordered_heap<TYPE>* heap_init(bool type, array<TYPE>* arr){
    ordered_heap<TYPE>* heap = (ordered_heap<TYPE>*)malloc(sizeof(ordered_heap<TYPE>));
    heap->type = type;
    heap->max_size = 1.5 * arr->size();
    heap->size = arr->size();
    heap->data = (TYPE*)malloc(sizeof(TYPE) * 1.5 * arr->size());
    for (int i = 0; i < arr->size(); ++i) {
        heap->data[i] = arr->get(i);
    }
    for (int i = arr->size() / 2; i > 0; --i) {
        heap_down(heap, i);
    }
    return heap;
}

// 堆元素下沉调整操作
T void heap_down(ordered_heap<TYPE>* heap, int order){
    int cur = order;
    while (heap_check_order(heap, get_left(cur))){
        int child = get_prior_child(heap, cur);
        if (higher_priority(heap, cur, child)){
            break;
        }
        swap(heap->data, cur - 1, child - 1);
        cur = child;
    }
}

// 堆元素上浮调整操作
T void heap_up(ordered_heap<TYPE>* heap, int order){
    int cur = order;
    int parent = get_parent(cur);
    while (cur != 1 && higher_priority(heap, cur, parent)){
        swap(heap->data, cur - 1, parent - 1);
        cur = parent;
        parent = get_parent(cur);
    }
}

// 将元素插入堆中
T void heap_add(ordered_heap<TYPE>* heap, TYPE e){
    if (heap_check_full(heap)){
        INSERT_ERROR;
    }
    heap->size += 1;
    heap->data[heap->size - 1] = e;
    heap_up(heap, heap->size);
}

// 将优先级最高的元素弹出并返回
T TYPE heap_pop(ordered_heap<TYPE>* heap){
    if (heap_check_empty(heap)){
        POP_ERROR;
    }
    TYPE res = heap->data[0];
    swap(heap->data, 0, heap->size - 1);
    heap_down(heap, 1);
    heap->size -= 1;
    return res;
}

// 打印顺序堆
T void heap_print(ordered_heap<TYPE>* heap){
    if (heap->type){
        std::cout << "max: ";
    } else{
        std::cout << "min: ";
    }
    if (!heap_check_empty(heap)){
        std::cout << heap_get_top(heap);
    } else{
        std::cout << "NULL";
    }
    std::cout << " {";
    for (int i = 0; i < heap->size; ++i) {
        std::cout << heap->data[i] << ", ";
    }
    std::cout << "}";
}
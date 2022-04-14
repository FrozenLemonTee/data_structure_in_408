//
// Created by Lenovo on 2022/4/5.
//

#ifndef C_C___STATIC_LINKED_LIST_H
#define C_C___STATIC_LINKED_LIST_H

#endif //C_C___STATIC_LINKED_LIST_H
#include "global.h"

// 静态链表定义
typedef struct static_linked_list {
    int** list_body; // 指向表本体的指针
    int head_node; // 储存链表体首节点存储下标
    int tail_node; // 储存链表体尾结点存储下标
    int max_size; // 表本体最大长度
    int cnt; // 表中当前元素个数
}static_linked_list;

// 静态链表初始化
static_linked_list* list_init(int max_size){
    static_linked_list* list = (static_linked_list*)std::malloc(sizeof(static_linked_list));
    list->list_body = (int**)std::malloc(sizeof(int*) * (max_size + 1));
    list->list_body[0] = (int*)std::malloc(sizeof(int) * 2);
    list->list_body[0][0] = INT_MAX;
    list->list_body[0][1] = 0;
    for (int i = 0; i < max_size; ++i) {
        list->list_body[i+1] = (int*)std::malloc(sizeof(int) * 2);
        list->list_body[i+1][1] = -1;
    }
    list->head_node = 0;
    list->tail_node = 0;
    list->max_size = max_size;
    list->cnt = 0;
    return list;
}

// 求顺序表当前表长
int list_length(static_linked_list* list){
    return list->cnt;
}

// 检查链表是否为空
bool list_check_empty(static_linked_list* list){
    return !list_length(list);
}

// 检查传入的存储下标是否合法
bool list_check_suffix(static_linked_list* list, int suffix){
    return suffix >= 0 && suffix < list->max_size + 1;
}

// 检查传入的索引是否合法
bool list_check_index(static_linked_list* list, int index){
    return index >= -1 && index < list->cnt;
}

// 辅助函数，检查静态链表是否达到最大长度
bool list_check_size(static_linked_list* list){
    return list_length(list) == list->max_size;
}

// 按存储下标查找某元素的值
int list_get_elem(static_linked_list* list, int suffix){
    if (!list_check_suffix(list, suffix)){
        ILLEGAL_SUFFIX;
    }
    return list->list_body[suffix][0];
}

// 获取当前节点的后继节点的存储下标
int list_get_suffix(static_linked_list* list, int suffix){
    if (!list_check_suffix(list, suffix)){
        ILLEGAL_SUFFIX;
    }
    return list->list_body[suffix][1];
}

// 设置当前节点的后继节点的储存下标
void list_set_suffix(static_linked_list* list, int suffix, int next){
    if (!list_check_suffix(list, suffix)){
        ILLEGAL_SUFFIX;
    }
    list->list_body[suffix][1] = next;
}

// 按索引查找某节点的存储下标
int list_find_suffix(static_linked_list* list, int index){
    if (!list_check_index(list, index)){
        ILLEGAL_INDEX;
    }
    int suffix = 0;
    for (int i = 0; i <= index; ++i) {
        suffix = list_get_suffix(list, suffix);
    }
    return suffix;
}

// 按值查找某一个元素的索引
int list_find_by_val(static_linked_list* list, int val){
    int suffix = 0;
    for (int i = -1; i <= list_length(list) && list_get_elem(list, suffix) != val; ++i) {
        suffix = list_get_suffix(list, suffix);
        if (list_get_elem(list, suffix) == val){
            return i + 1;
        }
    }
    return -1;
}

// 打印静态链表
void list_print(static_linked_list* list){
    std::cout << "[";
    for (int i = 1, suffix = list_get_suffix(list, 0);
    i < list_length(list) + 1; ++i, suffix = list_get_suffix(list, suffix)) {
        std::cout << list_get_elem(list, suffix) << ",";
    }
    std::cout << "]";
}

// 随机设置元素至空余空间中
int list_rand_set_elem(static_linked_list* list, int val){
    if (list_check_size(list)){
        INSERT_ERROR;
    }
    int suffix = rand_range(1, list->max_size);
    while (list_get_suffix(list, suffix) != -1){
        suffix = rand_range(1, list->max_size);
    }
    list->list_body[suffix][0] = val;
    list->cnt += 1;
    return suffix;
}

// 创建链表中第一个元素
void list_body_create(static_linked_list* list, int val){
    int cur = list_rand_set_elem(list, val);
    list->head_node = cur;
    list->tail_node = cur;
    list_set_suffix(list, 0, cur);
    list_set_suffix(list, cur, 0);
}

// 在链表尾部插入元素
void list_insert(static_linked_list* list, int val){
    if (list_check_empty(list)){
        list_body_create(list, val);
        return;
    }
    int cur = list_rand_set_elem(list, val);
    list_set_suffix(list, list->tail_node, cur);
    list->tail_node = cur;
}

// 在链表头部插入元素
void list_add_head(static_linked_list* list, int val){
    if (list_check_empty(list)){
        list_body_create(list, val);
        return;
    }
    int cur = list_rand_set_elem(list, val);
    list_set_suffix(list, cur, list->head_node);
    list_set_suffix(list, 0, cur);
    list->head_node = cur;
}

// 将元素插入链表中
void list_insert(static_linked_list* list, int index, int val){
    if (index == list_length(list)){
        list_insert(list, index);
        return;
    } else if (index == 0){
        list_add_head(list, val);
        return;
    } else if (!list_check_index(list, index)){
        ILLEGAL_INDEX;
    }
    int cur = list_rand_set_elem(list, val);
    int pre = list_find_suffix(list, index - 1);
    int pro = list_get_suffix(list, pre);
    list_set_suffix(list, pre, cur);
    list_set_suffix(list, cur, pro);
}

// 弹出头部的元素并返回
int list_pop(static_linked_list* list){
    if (list_check_empty(list)){
        POP_ERROR;
    }
    int cur = list_get_suffix(list, 0);
    list_set_suffix(list, 0, list_get_suffix(list, cur));
    list_set_suffix(list, cur, -1);
    list->cnt -= 1;
    return list_get_elem(list, cur);
}

// 弹出链表中的元素并返回
int list_pop(static_linked_list* list, int index){
    if (list_check_empty(list)){
        POP_ERROR;
    } else if (!list_check_index(list, index)){
        ILLEGAL_INDEX;
    }
    if (index == 0){
        return list_pop(list);
    }
    int pre = list_find_suffix(list, index - 1);
    int cur = list_get_suffix(list, pre);
    int pro = list_get_suffix(list, cur);
    list_set_suffix(list, pre, pro);
    list_set_suffix(list, cur, -1);
    list->cnt -= 1;
    return list_get_elem(list, cur);
}

// 清空链表的存储空间
void list_delete(static_linked_list* list){
    free(list);
}
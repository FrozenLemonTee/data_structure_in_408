//
// Created by Lenovo on 2022/3/30.
//

#ifndef C_C___ORDERED_LIST_H
#define C_C___ORDERED_LIST_H

#endif //C_C___ORDERED_LIST_H
#include "global.h"
#include "cstdlib"
#include "iostream"

// 顺序表结构体定义
typedef struct ordered_list {
    int* list_body; // 指向表本体的指针
    int max_size; // 表本体最大长度
    int cnt; // 表中当前元素个数
}ordered_list;

// 顺序表初始化
ordered_list* list_init(int max_size){
    ordered_list* list = (ordered_list*)std::malloc(sizeof(ordered_list));
    list->list_body = (int*)std::malloc(sizeof(int) * max_size);
    list->max_size = max_size;
    list->cnt = 0;
    return list;
}

// 求顺序表当前表长
int list_length(ordered_list* list){
    return list->cnt;
}

// 辅助函数，检查索引是否非法
void index_check(ordered_list* list, int index){
    if (index < 0 || index >= list_length(list)){
        error("Illegal index", 100);
    }
}

// 辅助函数，检查顺序表是否达到最大长度
bool max_size_check(ordered_list* list){
    return list_length(list) == list->max_size;
}

// 辅助函数，检查顺序表是否为空
bool empty_check(ordered_list* list){
    return !list_length(list);
}

// 按值查找某元素下标，找不到返回-1
int list_locate_elem(ordered_list* list, int val){
    for (int i = 0; i < list_length(list); ++i) {
        if (list->list_body[i] == val){
            return i;
        }
    }
    return -1;
}

// 按位查找某元素的值
int list_get_elem(ordered_list* list, int index){
    index_check(list, index);
    return list->list_body[index];
}

// 修改某一位的值
void list_set_elem(ordered_list* list, int index, int val){
    index_check(list, index);
    list->list_body[index] = val;
}

// 插入新元素
void list_insert(ordered_list* list, int index, int val){
    if (max_size_check(list)){
        error("Can not insert element", 101);
    }
    list->cnt += 1;
    for (int i = list_length(list) - 1; i > index; --i) {
        list_set_elem(list, i, list_get_elem(list, i-1));
    }
    list_set_elem(list, index, val);
}

// 将元素从表中删除并返回
int list_pop(ordered_list* list, int index){
    if (empty_check(list)){
        error("Can not pop element", 102);
    }
    int val = list_get_elem(list, index);
    for (int i = index; i < list_length(list) - 1; ++i) {
        list_set_elem(list, i, list_get_elem(list, i+1));
    }
    list->cnt -= 1;
    return val;
}

// 打印整个列表
void list_print(ordered_list* list){
    std::cout << "[";
    for (int i = 0; i < list_length(list); ++i) {
        std::cout << list_get_elem(list, i) << ",";
    }
    std::cout << "]";
}

// 清空列表的存储空间
void list_delete(ordered_list* list){
    free(list);
}
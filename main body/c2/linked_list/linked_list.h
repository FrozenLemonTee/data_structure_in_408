//
// Created by Lenovo on 2022/3/31.
//

#ifndef C_C___LINKED_LIST_H
#define C_C___LINKED_LIST_H

#endif //C_C___LINKED_LIST_H
#include "global.h"

// 单链表节点定义
T struct list_node{
    TYPE data; // 节点数据域
    list_node<TYPE>* next_node; // 节点指针域
};

// 打印节点
T void node_print(list_node<TYPE>* node){
    std::cout << "(" << node->data << ", #" << node->next_node << ")";
}

// 设置节点数据域的值
T void node_set_val(list_node<TYPE>* node, TYPE val){
    node->data = val;
}

// 设置节点指针域的地址
T void node_set_next(list_node<TYPE>* node, list_node<TYPE>* next){
    node->next_node = next;
}

// 单链表定义
T struct linked_list{
    list_node<TYPE> body_pointer; // 链表哨兵节点
    list_node<TYPE>* head_node; // 链表体首节点指针
    list_node<TYPE>* tail_node; // 链表体尾结点指针
    int cnt;
};

// 节点初始化
T list_node<TYPE>* node_init(TYPE data){
    list_node<TYPE>* node = (list_node<TYPE>*)malloc(sizeof(list_node<TYPE>));
    node_set_val(node, data);
    node_set_next(node, (list_node<TYPE>*)nullptr);
    return node;
}

// 返回链表长度
T int list_length(linked_list<TYPE>* list){
    return list->cnt;
}

// 打印单链表
T void list_print(linked_list<TYPE>* list){
    std::cout << "[";
    list_node<TYPE>* pointer = list->body_pointer.next_node;
    if (list_length(list)){
        for (int i = 0; i < list_length(list) - 1; ++i) {
            node_print(pointer);
            pointer = pointer->next_node;
            std::cout << "->";
        }
        node_print(pointer);
    }
    std::cout << "]";
}

// 检查链表是否为空
T bool list_check_empty(linked_list<TYPE>* list){
    return !list_length(list);
}

// 检查传入的索引是否合法
T bool list_check_index(linked_list<TYPE>* list, int index){
    return index >= -1 && index < list_length(list);
}

// 单链表初始化
T linked_list<TYPE>* list_init(){
    linked_list<TYPE>* list = (linked_list<TYPE>*)malloc(sizeof(linked_list<TYPE>));
    list->body_pointer = *node_init<TYPE>(nullptr);
    list->head_node = (list_node<TYPE>*)nullptr;
    list->tail_node = (list_node<TYPE>*)nullptr;
    list->cnt = 0;
    return list;
}

// 为链表创建第一个节点
T void list_body_create(linked_list<TYPE>* list, list_node<TYPE>* node){
    node_set_next(&list->body_pointer, node);
    list->head_node = node;
    list->tail_node = node;
    list->cnt += 1;
}

// 在链表尾部插入节点
T void list_insert(linked_list<TYPE>* list, list_node<TYPE>* node){
    if (list_check_empty(list)){
        list_body_create(list, node);
        return;
    }
    node_set_next(list->tail_node, node);
    list->tail_node = node;
    list->cnt += 1;
}

// 在链表头部插入节点
T void list_add_head(linked_list<TYPE>* list, list_node<TYPE>* node){
    if (list_check_empty(list)){
        list_body_create(list, node);
        return;
    }
    node_set_next(node, list->head_node);
    node_set_next(&list->body_pointer, node);
    list->head_node = node;
    list->cnt += 1;
}

// 按索引查找节点
T list_node<TYPE>* list_find_by_index(linked_list<TYPE>* list, int index){
    if (!list_check_index(list, index)){
        ILLEGAL_INDEX;
    }
    list_node<TYPE>* node_pointer = &list->body_pointer;
    for (int i = 0; i <= index; ++i) {
        node_pointer = node_pointer->next_node;
    }
    return node_pointer;
}

// 按值查找节点
T list_node<TYPE>* list_find_by_val(linked_list<TYPE>* list, TYPE val){
    list_node<TYPE>* node_pointer = &list->body_pointer;
    for (int i = 0; i <= list_length(list) && node_pointer->data != val; ++i) {
        node_pointer = node_pointer->next_node;
    }
    return node_pointer;
}

// 将节点插入链表中
T void list_insert(linked_list<TYPE>* list, int index, list_node<TYPE>* node){
    if (index == list_length(list)){
        list_insert(list, node);
        return;
    } else if (index == 0){
        list_add_head(list, node);
        return;
    } else if (!list_check_index(list, index)){
        ILLEGAL_INDEX;
    }
    list_node<TYPE>* pre_pointer = list_find_by_index(list, index - 1);
    list_node<TYPE>* pro_pointer = pre_pointer->next_node;
    node_set_next(pre_pointer, node);
    node_set_next(node, pro_pointer);
    list->cnt += 1;
}

// 弹出头部的节点并返回
T list_node<TYPE>* list_pop(linked_list<TYPE>* list){
    if (list_check_empty(list)){
        POP_ERROR;
    }
    list_node<TYPE>* node = list->head_node;
    node_set_next(&list->body_pointer, node->next_node);
    node_set_next(node, (list_node<TYPE>*)nullptr);
    list->cnt -= 1;
    list->head_node = list->body_pointer.next_node;
    return node;
}

// 弹出链表中的节点并返回
T list_node<TYPE>* list_pop(linked_list<TYPE>* list, int index){
    if (list_check_empty(list)){
        POP_ERROR;
    } else if (!list_check_index(list, index)){
        ILLEGAL_INDEX;
    }
    if (index == 0){
        return list_pop(list);
    }
    list_node<TYPE>* pre_pointer = list_find_by_index(list, index - 1);
    list_node<TYPE>* node = pre_pointer->next_node;
    list_node<TYPE>* pro_pointer = node->next_node;
    node_set_next(pre_pointer, pro_pointer);
    node_set_next(node, (list_node<TYPE>*)nullptr);
    list->cnt -= 1;
    return node;
}

// 清空链表的存储空间
T void list_delete(linked_list<TYPE>* list){
    free(list);
}
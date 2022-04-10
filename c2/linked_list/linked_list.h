//
// Created by Lenovo on 2022/3/31.
//

#ifndef C_C___LINKED_LIST_H
#define C_C___LINKED_LIST_H

#endif //C_C___LINKED_LIST_H
#include "global.h"
#include "iostream"

// 单链表节点定义
typedef struct list_node{
    int data; // 节点数据域
    list_node* next_node; // 节点指针域
}list_node;

// 打印节点
void node_print(list_node* node){
    std::cout << "(" << node->data << ", #" << node->next_node << ")";
}

// 设置节点数据域的值
void node_set_val(list_node* node, int val){
    node->data = val;
}

// 设置节点指针域的地址
void node_set_next(list_node* node, list_node* next){
    node->next_node = next;
}

// 单链表定义
typedef struct linked_list{
    list_node body_pointer; // 链表哨兵节点
    list_node* head_node; // 链表体首节点指针
    list_node* tail_node; // 链表体尾结点指针
    int cnt;
}linked_list;

// 节点初始化
list_node* node_init(int data){
    list_node* node = (list_node*)malloc(sizeof(list_node));
    node_set_val(node, data);
    node_set_next(node, NULL);
    return node;
}

// 返回链表长度
int list_length(linked_list* list){
    return list->cnt;
}

// 打印单链表
void list_print(linked_list* list){
    std::cout << "[";
    list_node* pointer = list->body_pointer.next_node;
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
bool list_check_empty(linked_list* list){
    return !list_length(list);
}

// 检查传入的索引是否合法
bool list_check_index(linked_list* list, int index){
    return index >= -1 && index < list_length(list);
}

// 单链表初始化
linked_list* list_init(){
    linked_list* list = (linked_list*)malloc(sizeof(linked_list));
    list->body_pointer = *node_init(INT_MAX);
    list->head_node = NULL;
    list->tail_node = NULL;
    list->cnt = 0;
    return list;
}

// 为链表创建第一个节点
void list_body_create(linked_list* list, list_node* node){
    node_set_next(&list->body_pointer, node);
    list->head_node = node;
    list->tail_node = node;
    list->cnt += 1;
}

// 在链表尾部插入节点
void list_insert(linked_list* list, list_node* node){
    if (list_check_empty(list)){
        list_body_create(list, node);
        return;
    }
    node_set_next(list->tail_node, node);
    list->tail_node = node;
    list->cnt += 1;
}

// 在链表头部插入节点
void list_add_head(linked_list* list, list_node* node){
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
list_node* list_find_by_index(linked_list* list, int index){
    if (!list_check_index(list, index)){
        ILLEGAL_INDEX;
    }
    list_node* node_pointer = &list->body_pointer;
    for (int i = 0; i <= index; ++i) {
        node_pointer = node_pointer->next_node;
    }
    return node_pointer;
}

// 按值查找节点
list_node* list_find_by_val(linked_list* list, int val){
    list_node* node_pointer = &list->body_pointer;
    for (int i = 0; i <= list_length(list) && node_pointer->data != val; ++i) {
        node_pointer = node_pointer->next_node;
    }
    return node_pointer;
}

// 将节点插入链表中
void list_insert(linked_list* list, int index, list_node* node){
    if (index == list_length(list)){
        list_insert(list, node);
        return;
    } else if (index == 0){
        list_add_head(list, node);
        return;
    } else if (!list_check_index(list, index)){
        ILLEGAL_INDEX;
    }
    list_node* pre_pointer = list_find_by_index(list, index - 1);
    list_node* pro_pointer = pre_pointer->next_node;
    node_set_next(pre_pointer, node);
    node_set_next(node, pro_pointer);
    list->cnt += 1;
}

// 弹出头部的节点并返回
list_node* list_pop(linked_list* list){
    if (list_check_empty(list)){
        POP_ERROR;
    }
    list_node* node = list->head_node;
    node_set_next(&list->body_pointer, node->next_node);
    node_set_next(node, NULL);
    list->cnt -= 1;
    list->head_node = list->body_pointer.next_node;
    return node;
}

// 弹出链表中的节点并返回
list_node* list_pop(linked_list* list, int index){
    if (list_check_empty(list)){
        POP_ERROR;
    } else if (!list_check_index(list, index)){
        ILLEGAL_INDEX;
    }
    if (index == 0){
        return list_pop(list);
    }
    list_node* pre_pointer = list_find_by_index(list, index - 1);
    list_node* node = pre_pointer->next_node;
    list_node* pro_pointer = node->next_node;
    node_set_next(pre_pointer, pro_pointer);
    node_set_next(node, NULL);
    list->cnt -= 1;
    return node;
}

// 清空链表的存储空间
void list_delete(linked_list* list){
    free(list);
}
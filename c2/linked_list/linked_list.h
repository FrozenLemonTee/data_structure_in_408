//
// Created by Lenovo on 2022/3/31.
//

#ifndef C_C___LINKED_LIST_H
#define C_C___LINKED_LIST_H

#endif //C_C___LINKED_LIST_H
#include "cstdlib"
#include "iostream"

// 单链表节点定义
typedef struct list_node{
    int data; // 节点数据域
    list_node* next_node; // 节点指针域
}list_node;

// 设置节点数据域的值
void list_node_set_val(list_node* node, int val){
    node->data = val;
}

// 设置节点指针域的地址
void list_node_set_next(list_node* node, list_node* next){
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
list_node* list_node_init(int data){
    list_node* node = (list_node*)malloc(sizeof(list_node));
    list_node_set_val(node, data);
    list_node_set_next(node, NULL);
    return node;
}

// 单链表初始化
linked_list* linked_list_init(){
    linked_list* list = (linked_list*)malloc(sizeof(linked_list));
    list->body_pointer = *list_node_init(INT_MAX);
    list->head_node = &list->body_pointer;
    list->tail_node = &list->body_pointer;
    list->cnt = 0;
    return list;
}
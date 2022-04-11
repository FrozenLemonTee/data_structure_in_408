//
// Created by Lenovo on 2022/4/10.
//

#ifndef C_C___LINKED_STACK_H
#define C_C___LINKED_STACK_H

#endif //C_C___LINKED_STACK_H
#include "global.h"

// 链栈节点定义
typedef struct stack_node{
    int data; // 节点数据域
    stack_node* next_node; // 节点指针域
}stack_node;

// 打印节点
void node_print(stack_node* node){
    std::cout << "(" << node->data << ", #" << node->next_node << ")";
}

// 设置节点数据域的值
void node_set_val(stack_node* node, int val){
    node->data = val;
}

// 设置节点指针域的地址
void node_set_next(stack_node* node, stack_node* next){
    node->next_node = next;
}

// 节点初始化
stack_node* node_init(int data){
    stack_node* node = (stack_node*)malloc(sizeof(stack_node));
    node_set_val(node, data);
    node_set_next(node, NULL);
    return node;
}

// 链栈定义
typedef struct linked_stack{
    stack_node body_pointer; // 链栈哨兵节点
    int cnt;
}linked_stack;

// 单链表初始化
linked_stack* stack_init(){
    linked_stack* list = (linked_stack*)malloc(sizeof(linked_stack));
    list->body_pointer = *node_init(INT_MAX);
    list->cnt = 0;
    return list;
}

// 返回链表长度
int stack_length(linked_stack* stack){
    return stack->cnt;
}

// 检查链栈是否为空
bool stack_check_empty(linked_stack* stack){
    return !stack_length(stack);
}

// 打印链栈
void stack_print(linked_stack* stack){
    std::cout << "[";
    stack_node* pointer = stack->body_pointer.next_node;
    if (stack_length(stack)){
        for (int i = 0; i < stack_length(stack) - 1; ++i) {
            node_print(pointer);
            pointer = pointer->next_node;
            std::cout << "<-";
        }
        node_print(pointer);
    }
    std::cout << "]";
}

// 获取栈顶节点
stack_node* stack_get_top(linked_stack* stack){
    if (stack_check_empty(stack)){
        ILLEGAL_INDEX;
    }
    return stack->body_pointer.next_node;
}

// 弹出栈顶节点并返回
stack_node* stack_pop(linked_stack* stack){
    stack_node* node = stack_get_top(stack);
    node_set_next(&stack->body_pointer, node->next_node);
    node_set_next(node, NULL);
    stack->cnt -= 1;
    return node;
}

// 将元素置于栈顶
void stack_push(linked_stack* stack, stack_node* node){
    stack->cnt += 1;
    node_set_next(node, stack_get_top(stack));
    node_set_next(&stack->body_pointer, node);
}

// 删除顺序栈
void stack_delete(linked_stack* stack){
    free(stack);
}
//
// Created by Lenovo on 2022/4/10.
//

#ifndef C_C___ORDERED_STACK_H
#define C_C___ORDERED_STACK_H

#endif //C_C___ORDERED_STACK_H
#include "global.h"

// 顺序栈结构定义
typedef struct ordered_stack{
    int* stack_body; // 指向栈本体的指针
    int max_size; // 栈本体最大长度
    int cnt; // 表中当前元素个数
}ordered_stack;

// 顺序栈初始化
ordered_stack* stack_init(int max_size){
    ordered_stack* stack = (ordered_stack*)std::malloc(sizeof(ordered_stack));
    stack->stack_body = (int*)std::malloc(sizeof(int) * max_size);
    stack->max_size = max_size;
    stack->cnt = 0;
    return stack;
}

// 求顺序栈当前栈中元素个数
int stack_length(ordered_stack* stack){
    return stack->cnt;
}

// 检查顺序栈是否达到最大长度
bool max_size_check(ordered_stack* stack){
    return stack_length(stack) == stack->max_size;
}

// 检查顺序栈是否为空
bool empty_check(ordered_stack* stack){
    return !stack_length(stack);
}

// 获取栈顶元素的值
int stack_get_top(ordered_stack* stack){
    if (empty_check(stack)){
        ILLEGAL_INDEX;
    }
    return stack->stack_body[stack->cnt - 1];
}

// 弹出栈顶元素并返回
int stack_pop(ordered_stack* stack){
    int val = stack_get_top(stack);
    stack->cnt -= 1;
    return val;
}

// 将元素置于栈顶
void stack_push(ordered_stack* stack, int val){
    if (max_size_check(stack)){
        INSERT_ERROR;
    }
    stack->cnt += 1;
    stack->stack_body[stack->cnt - 1] = val;
}

// 打印顺序栈
void stack_print(ordered_stack* stack){
    std::cout << "[";
    for (int i = 0; i < stack_length(stack); ++i) {
        std::cout << stack->stack_body[i] << ",";
    }
    std::cout << "]";
}

// 删除顺序栈
void stack_delete(ordered_stack* stack){
    free(stack);
}
//
// Created by Lenovo on 2022/4/10.
//
#include "ordered_stack.h"


#define LEN 50

void test_show_top(ordered_stack * stack){
    if (!empty_check(stack)){
        std::cout << ", top: " << stack_get_top(stack);
    } else{
        std::cout << ", top: NULL";
    }
}

// flag: 是否输出提示信息
void test_push(ordered_stack * stack, int num, int flag){
    for (int i = 0; i < num; ++i) {
        int val = rand_range(0, stack_length(stack));
        if (flag){
            std::cout << "cur elem: " << val << " ";
        }
        stack_push(stack, val);
        if (flag){
            stack_print(stack);
            test_show_top(stack);
            std::cout << std::endl;
        }
    }
}


void test_pop(ordered_stack* stack, int num){
    for (int i = 0; i < num; ++i) {
        int val = stack_pop(stack);
        std::cout << "cur elem: " << val << " ";
        test_show_top(stack);
        stack_print(stack);
        std::cout << std::endl;
    }
}

void test_delete(ordered_stack* stack){
    std::cout << "before: ";
    stack_print(stack);
    std::cout << std::endl;
    stack_delete(stack);
    std::cout << "after: ";
    stack_print(stack);
    std::cout << std::endl;
}

int main(){
    ordered_stack * stack = stack_init(50);
    test_push(stack, LEN, 1);
    std::cout << "-----------------------" << std::endl;
    test_pop(stack, LEN);
    std::cout << "-----------------------" << std::endl;
    test_push(stack, LEN, 0);
    test_delete(stack);
    return 0;
}
//
// Created by Lenovo on 2022/4/10.
//

#include "linked_stack.h"
#define LEN 15


void test_show_top(linked_stack* stack){
    if (!stack_check_empty(stack)){
        std::cout << ", top: ";
        node_print(stack_get_top(stack));
    } else{
        std::cout << ", top: NULL";
    }
}

// flag: 是否输出提示信息
void test_push(linked_stack * stack, int num, int flag){
    for (int i = 0; i < num; ++i) {
        int val = rand_range(0, stack_length(stack));
        if (flag){
            std::cout << "cur elem: " << val << " ";
        }
        stack_push(stack, node_init(val));
        if (flag){
            stack_print(stack);
            test_show_top(stack);
            std::cout << std::endl;
        }
    }
}


void test_pop(linked_stack* stack, int num){
    for (int i = 0; i < num; ++i) {
        stack_node* node = stack_pop(stack);
        std::cout << "cur elem: " << node->data << " ";
        test_show_top(stack);
        stack_print(stack);
        std::cout << std::endl;
    }
}

void test_delete(linked_stack* stack){
    std::cout << "before: ";
    stack_print(stack);
    std::cout << std::endl;
    stack_delete(stack);
    std::cout << "after: ";
    stack_print(stack);
    std::cout << std::endl;
}

int main(){
    linked_stack* stack = stack_init();
    test_push(stack, LEN, 1);
    std::cout << "-----------------------" << std::endl;
    test_pop(stack, LEN);
    std::cout << "-----------------------" << std::endl;
    test_push(stack, LEN, 0);
    test_delete(stack);
    return 0;
}
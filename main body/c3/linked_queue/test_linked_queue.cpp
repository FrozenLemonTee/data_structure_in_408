//
// Created by Lenovo on 2022/4/12.
//
#include "linked_queue.h"
#define LEN 20

// flag为1，打印对头元素；flag为0，打印队尾元素
T void test_show_end(linked_queue::linked_queue<TYPE>* queue, int flag){
    if (!queue_check_empty(queue)){
        if (flag){
            std::cout << "front: ";
            node_print(queue_get_front(queue));
        } else{
            std::cout << "tail: ";
            node_print(queue_get_tail(queue));
        }
    } else{
        std::cout << "front/tail: NULL";
    }
}

// flag为1，输出提示信息；flag为0，不输出提示信息
T void test_push(linked_queue::linked_queue<TYPE>* queue, int num, int flag){
    for (int i = 0; i < num; ++i) {
        int val = rand_range(0, LEN);
        if (flag){
            std::cout << "cur elem: " << val << ", ";
        }
        queue_push_(queue, linked_queue::queue_node_init<TYPE>(val));
        if (flag){
            test_show_end(queue, 1);
            std::cout << ", cur queue: ";
            queue_print(queue);
            std::cout << ", ";
            test_show_end(queue, 0);
            std::cout << std::endl;
        }
    }
}
// flag为1，输出提示信息；flag为0，不输出提示信息
T void test_pop(linked_queue::linked_queue<TYPE>* queue, int num, int flag){
    for (int i = 0; i < num; ++i) {
        int val = node_get_val(queue_pop_(queue));
        if (flag){
            std::cout << "cur elem: " << val << ", ";
            test_show_end(queue, 1);
            std::cout << ", cur queue: ";
            queue_print(queue);
            std::cout << ", ";
            test_show_end(queue, 0);
            std::cout << std::endl;
        }
    }
}

T void test_push_and_pop(linked_queue::linked_queue<TYPE>* queue, int num){
    for (int i = 0; i < num; ++i) {
        std::cout << "cur operation: ";
        bool op = rand_bool();
        if (op){
            std::cout << "push." << std::endl;
            test_push(queue, 1, 1);
        } else{
            std::cout << "pop." << std::endl;
            test_pop(queue, 1, 1);
        }

    }
}

int main(){
    linked_queue::linked_queue<int>* queue1 = linked_queue::queue_init<int>();
    test_push(queue1, 0.5*LEN, 1);
    std::cout << "-----------------------" << std::endl;
    test_pop(queue1, 0.5*LEN, 1);
    std::cout << "-----------------------";
    linked_queue::linked_queue<int>* queue2 = linked_queue::queue_init<int>();
    test_push(queue2, 0.1*LEN, 0);
    std::cout << std::endl;
    queue_print(queue2);
    std::cout << std::endl;
    test_push_and_pop(queue2, LEN);
    return 0;
}
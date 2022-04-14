//
// Created by Lenovo on 2022/4/11.
//

#include "circular_queue.h"

#define LEN 50

// flag为1，打印对头元素；flag为0，打印队尾元素
void test_show_end(circular_queue* queue, int flag){
    if (!queue_empty_check(queue)){
        if (flag){
            std::cout << "front: " << queue_get_front(queue);
        } else{
            std::cout << "tail: " << queue_get_tail(queue);
        }
    } else{
        std::cout << "front/tail: NULL";
    }
}

// flag为1，输出提示信息；flag为0，不输出提示信息
void test_push(circular_queue* queue, int num, int flag){
    for (int i = 0; i < num; ++i) {
        int val = rand_range(0, LEN);
        if (flag){
            std::cout << "cur elem: " << val << ", ";
        }
        queue_push(queue, val);
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
void test_pop(circular_queue* queue, int num, int flag){
    for (int i = 0; i < num; ++i) {
        int val = queue_pop(queue);
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

void test_push_and_pop(circular_queue* queue, int num){
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
    circular_queue* queue1 = queue_init(LEN);
    test_push(queue1, 0.5*LEN, 1);
    std::cout << "-----------------------" << std::endl;
    test_pop(queue1, 0.5*LEN, 1);
    std::cout << "-----------------------";
    circular_queue* queue2 = queue_init(LEN);
    test_push(queue2, 0.1*LEN, 0);
    std::cout << std::endl;
    queue_print(queue2);
    std::cout << std::endl;
    test_push_and_pop(queue2, LEN);
    return 0;
}
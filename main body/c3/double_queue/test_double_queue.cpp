//
// Created by Lenovo on 2022/4/14.
//
#include "double_queue.h"
#define LEN 50

// flag为1，打印对头元素；flag为0，打印队尾元素
void test_show_end(double_queue* queue, int flag){
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

// flag为1，输出提示信息；flag为0，不输出提示信息;
// pos为1，对队头操作；pos为0，对队尾操作
void test_push(double_queue* queue, int num, int flag, int pos){
    for (int i = 0; i < num; ++i) {
        int val = rand_range(0, LEN);
        if (flag){
            std::cout << "cur elem: " << val << ", ";
        }
        if (pos){
            queue_push_front(queue, val);
        } else{
            queue_push_tail(queue, val);
        }
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
// pos为1，对队头操作；pos为0，对队尾操作
void test_pop(double_queue* queue, int num, int flag, int pos){
    for (int i = 0; i < num; ++i) {
        int val;
        if (pos){
            val = queue_pop_front(queue);
        } else{
            val = queue_pop_tail(queue);
        }
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

void test_push_and_pop(double_queue* queue, int num){
    for (int i = 0; i < num; ++i) {
        // op为1，入队操作；op为0，出队操作
        bool op = rand_bool();
        bool pos = rand_bool();
        std::cout << "cur position: ";
        if (pos){
            std::cout << "front." << std::endl;
        } else{
            std::cout << "tail." << std::endl;
        }
        std::cout << "cur operation: ";
        if (op){
            std::cout << "push." << std::endl;
            test_push(queue, 1, 1, pos);
        } else{
            std::cout << "pop." << std::endl;
            test_pop(queue, 1, 1, pos);
        }
    }
}

int main(){
    double_queue* queue1 = queue_init(LEN);
    test_push(queue1, 0.25*LEN, 1, 0);
    test_push(queue1, 0.25*LEN, 1, 1);
    std::cout << "-----------------------" << std::endl;
    test_pop(queue1, 0.25*LEN, 1, 0);
    test_pop(queue1, 0.25*LEN, 1, 1);
    std::cout << "-----------------------";
    double_queue* queue2 = queue_init(LEN);
    test_push(queue2, 0.1*LEN, 0 , 0);
    std::cout << std::endl;
    queue_print(queue2);
    std::cout << std::endl;
    test_push_and_pop(queue2, LEN);
    return 0;
}
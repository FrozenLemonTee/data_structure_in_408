//
// Created by Lenovo on 2022/4/21.
//
#include "nest_list.h"
#define COUNT 25
#define NEST 3
#define SEED 0.25

node<int>* recur_list_build(int* init){
    init[1] -= 1;
    node<int>* res = node_init<int>();
    while (init[0] > 0){
        float f = rand_double();
        if (f > SEED || init[1] == 0){
            node_add_end(res, node_init(rand_range(0, init[0])));
        } else{
            node_add_end(res, recur_list_build(init));
        }
        init[0] -= 1;
    }
    return res;
}

node<int>* list_build(int count, int nests){
    int* init = (int*)malloc(sizeof(int) * 2);
    init[0] = count, init[1] = nests;
    return recur_list_build(init);
}

void whole_list_print(node<int>* node){
    ::node<int>* n_queue[node_length(node)];
    ::node<int>* pointer = node->type_pointer;
    int p = 0;
    for (int i = 0; i < node_length(node); ++i) {
        if (node_type_check(pointer, 1)){
            n_queue[p] = pointer;
            p += 1;
        }
        pointer = pointer->next;
    }
    std::cout << "root node ";
    node_print(node);
    std::cout << ", count: " << node_count(node) << ", depth: " << node_depth(node) << ": " << std::endl;
    node_list_print(node);
    for (int i = 0; i < p; ++i) {
        std::cout << "> ";
        node_print(n_queue[i]);
        std::cout << ", count: " << node_count(n_queue[i]) << ", depth: " << node_depth(n_queue[i]) << ": " << std::endl;
        node_list_print(n_queue[i]);
        std::cout << std::endl;
    }
}

// flag为1，输出提示信息；flag为0，不输出提示信息
void test_add(node<int>* node, int num, int flag){
    for (int i = 0; i < num; ++i) {
        if (flag){
            std::cout << "before:" << std::endl;
            whole_list_print(node);
        }
        ::node<int>* end = list_build(COUNT, NEST);
        if (flag){
            std::cout << "add: ";
            node_print(end);
            std::cout << std::endl;
        }
        node_add_end(node, end);
        if (flag){
            std::cout << "after:" << std::endl;
            whole_list_print(node);
        }
    }
}

// flag为1，输出提示信息；flag为0，不输出提示信息
void test_delete(node<int>* node, int num, int flag){
    for (int i = 0; i < num; ++i) {
        if (flag){
            std::cout << "before:" << std::endl;
            whole_list_print(node);
        }
        ::node<int>* cur = node_delete_end(node);
        if (flag){
            std::cout << "cur delete: ";
            node_print(cur);
            std::cout << std::endl;
        }
        if (flag){
            std::cout << "after:" << std::endl;
            whole_list_print(node);
        }
    }
}

int main(){
    node<int>* node = list_build(COUNT, NEST);
    whole_list_print(node);
    std::cout << "-----------------------" << std::endl;
    test_add(node, 3, 1);
    std::cout << "-----------------------" << std::endl;
    test_delete(node, 7, 1);
    return 0;
}
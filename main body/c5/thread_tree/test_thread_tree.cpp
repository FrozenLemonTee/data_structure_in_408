//
// Created by Lenovo on 2022/5/17.
//
#include "thread_tree.h"
#define LEN 40

array<int> arr_create(int len){
    array<int> arr = array<int>(len);
    for (int i = 0; i < len; ++i) {
        arr.set(i, rand_range(0, i));
    }
    return arr;
}

int main(){
    array<int> arr = arr_create(LEN);
    arr.print();
    std::cout << std::endl;
    print_separate();
    thread_tree<int>* tree = r_tree_init(binary_tree::tree_init(arr));
    std::cout << tree->cnt << std::endl;
    return 0;
}
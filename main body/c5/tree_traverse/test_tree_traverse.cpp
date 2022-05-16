//
// Created by Lenovo on 2022/5/16.
//
#include "tree_traverse.h"
#define LEN 15
typedef void (*func_traverse)(binary_tree::binary_tree<int>*);

void TRAVERSE(binary_tree::binary_tree<int>* tree, func_traverse func_t){
    func_t(tree);
}

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
    binary_tree::binary_tree<int>* tree = binary_tree::tree_init<int>(arr);
    TRAVERSE(tree, tree_level_traverse);
    std::cout << std::endl;
    print_separate();
    TRAVERSE(tree, tree_pre_traverse);
    std::cout << std::endl;
    print_separate();
    TRAVERSE(tree, tree_in_traverse);
    std::cout << std::endl;
    print_separate();
    TRAVERSE(tree, tree_post_traverse);
    return 0;
}
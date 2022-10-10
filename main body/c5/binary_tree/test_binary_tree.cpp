//
// Created by Lenovo on 2022/5/13.
//
#include "binary_tree.h"
#define LEN 40

array<int> arr_create(int len){
    array<int> arr = array<int>(len);
    for (int i = 0; i < len; ++i) {
        arr.set(i, rand_range(0, i));
    }
    return arr;
}

int main(){
    std::cout << node_check_null((binary_tree::tree_node<int> *) nullptr);
    std::cout << std::endl;
    binary_tree::binary_tree<int>* tree1 = binary_tree::tree_init<int>();
    std::cout << tree_check_empty(tree1) << std::endl;
    array<int> arr = arr_create(LEN);
    arr.print();
    std::cout << std::endl;
    binary_tree::binary_tree<int>* tree2 = binary_tree::tree_init<int>(arr);
    std::cout << tree_check_empty(tree2) << std::endl;
//    binary_tree::binary_tree<int>* tree3 = binary_tree::tree_init(array<int>(5));
//    binary_tree::tree_node<int>* child = tree3->root->left;
//    binary_tree::node_print(child);
//    *child = *binary_tree::tree_node_init(6);
//    binary_tree::node_print(tree3->root->left);
    return 0;
}
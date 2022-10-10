//
// Created by Lenovo on 2022/10/9.
//

#include "AVL_tree.h"


int main(){
    AVL_tree<int>* tree = tree_init<int>();
    for (int i = 1; i < 11; ++i) {
        tree_insert(tree, i);
    }
    return 0;
}
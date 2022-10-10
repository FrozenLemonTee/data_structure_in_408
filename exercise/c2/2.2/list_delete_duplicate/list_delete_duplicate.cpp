//
// Created by Lenovo on 2022/10/9.
//

#include <main body/c2/ordered_list/ordered_list.h>
#include "main body/c7/AVL_tree/AVL_tree.h"

// 2023 2.2 05.
void delete_duplicate(ordered_list* list){
    AVL_tree<int>* tree = tree_init<int>();
    for (int i = 0; i < list_length(list); ++i) {
        if (tree_contains(tree, list_get(list, i))){
            list_pop(list, i);
            i -= 1;
        } else{
            tree_insert(tree, list_get(list, i));
        }
    }
}

#define LEN 30

void test(int cnt){
    for (int i = 0; i < cnt; ++i) {
        ordered_list* list = list_init(LEN);
        for (int j = 0; j < LEN * 0.4; ++j) {
            list_insert(list, list_length(list), rand_range(0, LEN));
        }
        std::cout << "before: ";
        list_print(list);
        std::cout << std::endl;
        delete_duplicate(list);
        std::cout << "after: ";
        list_print(list);
        std::cout << std::endl;
    }
}

int main(){
    test(LEN * 0.2);
    return 0;
}
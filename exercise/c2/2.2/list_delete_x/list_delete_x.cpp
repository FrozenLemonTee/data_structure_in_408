//
// Created by Lenovo on 2022/10/9.
//

#include "main body/c2/ordered_list/ordered_list.h"

// 2023 2.2 03.
void delete_x(ordered_list* list, int x){
    if (empty_check(list)){
        POP_ERROR;
    }
    for (int i = 0; i < list_length(list); ++i) {
        if (list_get(list, i) == x){
            list_pop(list, i);
            i -= 1;
        }
    }
}

#define LEN 10

ordered_list* list_create(int size){
    ordered_list* list = list_init(size);
    for (int i = 0; i < size; ++i) {
        list_insert(list, list_length(list), rand_range(0, size));
    }
    return list;
}

void test(int cnt, int x){
    for (int i = 0; i < cnt; ++i) {
        ordered_list* list = list_create(rand_range(0, LEN));
        std::cout << "before:";
        list_print(list);
        std::cout << std::endl;
        delete_x(list, x);
        std::cout << "after:";
        list_print(list);
        std::cout << std::endl;
    }
}

int main(){
    test(20, 6);
    return 0;
}
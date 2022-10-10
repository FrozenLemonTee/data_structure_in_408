//
// Created by Lenovo on 2022/10/9.
//

#include "main body/c2/ordered_list/ordered_list.h"

// 2023 2.2 02.
void reverse(ordered_list* list){
    for (int i = 0; i < list_length(list) / 2; ++i) {
        swap(list->list_body, i, list_length(list) - 1 - i);
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

void test(int cnt){
    for (int i = 0; i < cnt; ++i) {
        ordered_list* list = list_create(rand_range(0, LEN));
        std::cout << "before:";
        list_print(list);
        std::cout << std::endl;
        reverse(list);
        std::cout << "after:";
        list_print(list);
        std::cout << std::endl;
    }
}

int main(){
    test(20);
    return 0;
}
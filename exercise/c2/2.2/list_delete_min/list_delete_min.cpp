//
// Created by Lenovo on 2022/10/9.
//

#include "main body/c2/ordered_list/ordered_list.h"

// 2023 2.2 01.
int delete_min(ordered_list* list){
    if (empty_check(list)){
        POP_ERROR;
    }
    int index = 0;
    for (int i = 0; i < list_length(list); ++i) {
        if (list_get(list, i) < list_get(list, index)){
            index = i;
        }
    }
    return list_pop(list, index);
}

#define LEN 50

void test(ordered_list* list, int cnt){
    std::cout << "before:";
    list_print(list);
    std::cout << std::endl;
    for (int i = 0; i < cnt; ++i) {
        std::cout << "delete: " << delete_min(list) << std::endl;
        std::cout << "after:";
        list_print(list);
        std::cout << std::endl;
    }
}

int main(){
    ordered_list* list = list_init(LEN);
    for (int i = 0; i < LEN; ++i) {
        list_insert(list, i, rand_range(0, LEN));
    }
    test(list, LEN * 0.4);
    return 0;
}
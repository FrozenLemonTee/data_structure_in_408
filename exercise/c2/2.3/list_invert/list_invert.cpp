//
// Created by Lenovo on 2022/10/23.
//

#include "main body/c2/linked_list/linked_list.h"

void list_invert(linked_list<int>* list){
    for (int i = 0; i < list_length(list) / 2; ++i) {
        swap(list_find_by_index_(list, i)->data,
             list_find_by_index_(list, list_length(list) - 1 - i)->data);
    }
}

void test(array<int> arr){
    linked_list<int>* list = list_init<int>();
    for (int i = 0; i < arr.size(); ++i) {
        list_insert(list, arr.get(i));
    }
    std::cout << "before: ";
    list_print(list, true);
    list_invert(list);
    std::cout << "after: ";
    list_print(list, true);
}

int main(){
    test(array<int>({}));
    test(array<int>({2}));
    test(array<int>({4, 3, 5, 2, 1, 7}));
    test(array<int>({9, 3, 5, 6, 2, 1, 4}));
    return 0;
}
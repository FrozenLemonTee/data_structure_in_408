//
// Created by Lenovo on 2022/10/23.
//

#include "main body/c2/linked_list/linked_list.h"

T void list_recur_print(linked_list<TYPE>* list, list_node<TYPE>* node){
    if (node->next_node){
        list_recur_print(list, node->next_node);
    }
    if (node != &list->body_pointer){
        std::cout << "(#" << node << ", " << node->data << ") <-";
    }
}

T void list_reverse_print(linked_list<TYPE>* list){
    list_recur_print(list, list->head_node);
}

#define LEN 20

void test(int cnt){
    for (int i = 0; i < cnt; ++i) {
        linked_list<int>* list = list_init<int>();
        for (int j = 0; j < LEN; ++j) {
            list_insert(list, rand_range(0, LEN));
        }
        std::cout << "normal: " << std::endl;
        list_print(list, true);
        std::cout << "reversed print: " << std::endl;
        list_reverse_print(list);
        std::cout <<std::endl;
    }
}

int main(){
    test(LEN);
    return 0;
}
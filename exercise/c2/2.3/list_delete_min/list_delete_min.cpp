//
// Created by Lenovo on 2022/10/23.
//

#include "main body/c2/linked_list/linked_list.h"

bool list_delete_min(linked_list<int>* list){
    if (!list_check_empty(list)){
        list_node<int>* pointer = &list->body_pointer;
        list_node<int>* pre_min = pointer;
        while (pointer->next_node){
            if (pointer->next_node->data < pre_min->next_node->data){
                pre_min = pointer;
            }
            pointer = pointer->next_node;
        }
        list->cnt -= 1;
        if (list->head_node == list->tail_node && list->tail_node == pre_min->next_node){
            free(pre_min->next_node);
            list->body_pointer.next_node = nullptr;
            list->head_node = list->body_pointer.next_node;
            list->tail_node = list->head_node;
        } else{
            if (pre_min->next_node == list->head_node){
                list_node<int>* tmp = pre_min->next_node;
                list->head_node = list->head_node->next_node;
                pre_min->next_node = list->head_node;
                free(tmp);
            } else if (pre_min->next_node == list->tail_node){
                list_node<int>* tmp = pre_min->next_node;
                list->tail_node = pre_min;
                free(tmp);
                list->tail_node->next_node = nullptr;
            }else{
                list_node<int>* tmp = pre_min->next_node;
                pre_min->next_node = tmp->next_node;
                free(tmp);
            }
        }
        return true;
    }
    return false;
}

void test(array<int> arr){
    linked_list<int>* list = list_init<int>();
    for (int i = 0; i < arr.size(); ++i) {
        list_insert(list, arr.get(i));
    }
    std::cout << "before: ";
    list_print(list, true);
    list_delete_min(list);
    std::cout << "after: ";
    list_print(list, true);
}

int main(){
    test(array<int>({3, 4, 5, 2, 1, 7, 8, 6}));
    test(array<int>({3, 4, 5, 2, 6, 7, 8, 1}));
    test(array<int>({1, 4, 5, 2, 3, 7, 8, 6}));
    test(array<int>({3}));
    return 0;
}
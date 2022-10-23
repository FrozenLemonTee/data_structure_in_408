//
// Created by Lenovo on 2022/10/19.
//

#include "global.h"

typedef struct node{
    int data;
    node* next;
}list;

::node* list_delete_recur(::node* node, int val){
    if (node->next){
        node->next = list_delete_recur(node->next, val);
    }
    ::node* n_next = node;
    if (node->data == val){
        n_next = node->next;
        free(node);
    }
    return n_next;
}

void show(::list* list){
    ::node* pointer = list;
    while (pointer){
        std::cout << "(#" << pointer << ", " << pointer->data << ", #" << pointer->next << "), ";
        pointer = pointer->next;
    }
}

::list* create(array<int> arr){
    ::list* head = (::node*) malloc(sizeof(::node));
    head->data = INT_MAX;
    ::node* pointer = head;
    for (int i = 0; i < arr.size(); ++i) {
        pointer->next = (::node*) malloc(sizeof(::node));
        pointer = pointer->next;
        pointer->data = arr.get(i);
        pointer->next = nullptr;
    }
    return head;
}

#define LEN 10

void test(int cnt){
    for (int i = 0; i < cnt; ++i) {
        array<int> arr = array<int>(LEN * 2);
        for (int j = 0; j < arr.size(); ++j) {
            arr.set(j, rand_range(0, LEN));
        }
        ::list* list = create(arr);
        std::cout << "before: ";
        show(list);
        std::cout << std::endl;
        std::cout << "delete: ";
        int val = rand_range(0, LEN);
        std::cout << val << std::endl;
        list_delete_recur(list, val);
        std::cout << "after: ";
        show(list);
        std::cout << std::endl;
    }
}

int main(){
    test(LEN);
    return 0;
}
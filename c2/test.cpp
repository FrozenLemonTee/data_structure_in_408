#include "ordered_list.h"

#define LEN 50

int rand_index(int range_a, int range_b){
    return range_b ? range_a + rand() % range_b : range_a;
}

void test_insert(ordered_list* list, int num, int flag){
    for (int i = 0; i < num; ++i) {
        int index = rand_index(0, list_length(list));
        if (flag){
            std::cout << "cur index: " << index << ", " << "cur elem: " << i << " ";
        }
        list_insert(list, index, i);
        if (flag){
            list_print(list);
            std::cout << std::endl;
        }
    }
}


void test_pop(ordered_list* list, int num){
    for (int i = 0; i < num; ++i) {
        int index = rand_index(0, list_length(list));
        int val = list_pop(list, index);
        std::cout << "cur index: " << index << ", " << "cur elem: " << val << " ";
        list_print(list);
        std::cout << std::endl;
    }
}

void test_find_val(ordered_list* list, int num){
    for (int i = 0; i < num; ++i) {
        int val = rand_index(0, 2*LEN);
        int index = list_locate_elem(list, val);
        std::cout << "cur val: " << val << ", " << "cur elem index: " << index << " ";
        list_print(list);
        std::cout << std::endl;
    }
}

void test_delete(ordered_list* list){
    std::cout << "before: ";
    list_print(list);
    std::cout << std::endl;
    list_delete(list);
    std::cout << "after: ";
    list_print(list);
    std::cout << std::endl;
}

int main(){
    ordered_list* list = list_init(50);
    test_insert(list, LEN, 1);
    std::cout << "-----------------------" << std::endl;
    test_find_val(list, 10);
    std::cout << "-----------------------" << std::endl;
    test_pop(list, LEN);
    std::cout << "-----------------------" << std::endl;
    test_insert(list, LEN, 0);
    test_delete(list);
    return 0;
}
#include "ordered_list.h"

#define LEN 20

int main(){

    ordered_list* list = list_init(50);
    for (int i = 0; i < LEN; ++i) {
        list_insert(list, list_length(list), i);
        std::cout << list->list_body[i] << std::endl;
        std::cout << list->list_body[i] << std::endl;
        std::cout << list->list_body[i] << std::endl;
        std::cout << std::endl;
    }
    return 0;
}
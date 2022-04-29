//
// Created by Lenovo on 2022/4/25.
//
#include "my_string.h"

#define LEN 15

::string** str_create(int num){
    ::string** str_arr = (::string**)malloc(sizeof(::string*) * num);
    for (int i = 0; i < num; ++i) {
        str_arr[i] = str_init(rand_range(0, LEN));
        for (int j = 0; j < str_length(str_arr[i]); ++j) {
            str_set(str_arr[i], j + 1, rand_alpha());
        }
    }
    return str_arr;
}

void print_str(::string** str_arr, int num){
    for (int i = 0; i < num; ++i) {
        str_print(str_arr[i]);
        std::cout << std::endl;
    }
}

void test_plus(::string** str_arr, int num, int count){
    for (int i = 0; i < count; ++i) {
        int s1 = rand_range(0, num);
        int s2 = rand_range(0, num);
        str_print(str_arr[s1]);
        std::cout << " + ";
        str_print(str_arr[s2]);
        std::cout << " -> ";
        str_print(str_add(str_arr[s1], str_arr[s2]));
        std::cout << std::endl;
    }
}

void test_compare(::string** str_arr, int num, int count){
    for (int i = 0; i < count; ++i) {
        int s1 = rand_range(0, num);
        int s2 = rand_range(0, num);
        str_print(str_arr[s1]);
        std::cout << " == ";
        str_print(str_arr[s2]);
        std::cout << " -> " << str_compare(str_arr[s1], str_arr[s2]) << std::endl;
    }
}

void test_copy(::string** str_arr, int num){
    ::string** str_cpy = (::string**)malloc(sizeof(::string*) * num);
    for (int i = 0; i < num; ++i) {
        str_cpy[i] = str_init(str_arr[i]);
        std::cout << "#" << str_arr[i] << ": ";
        str_print(str_arr[i]);
        std::cout << " -> ";
        std::cout << "#" << str_cpy[i] << ": ";
        str_print(str_cpy[i]);
        std::cout << std::endl;
    }
}

void test_empty(::string* str){
    std::cout << "if #" << str << " is empty:" << str_empty(str) << std::endl;
}

void test_get(::string** str_arr, int num, int count){
    for (int i = 0; i < count; ++i) {
        int s = rand_range(0, num);
        int index = rand_range(1, str_length(str_arr[s]));
        str_print(str_arr[s]);
        std::cout << ", index: " << index << ", char: " << str_get(str_arr[s], index) << std::endl;
    }
}

void test_find(::string** str_arr, int num, int count){
    ::string* src = str_init();
    for (int i = 0; i < num; ++i) {
        int index = rand_range(0, num);
        src = str_add(src, str_arr[index]);
    }
    for (int i = 0; i < count; ++i) {
        int index = rand_range(0, num);
        ::string* ptn = str_arr[index];
        std::cout << "src: ";
        str_print(src);
        std::cout << std::endl;
        std::cout << "ptn: ";
        str_print(ptn);
        std::cout << std::endl;
        std::cout << "find: " << str_find(src, ptn) << std::endl;
    }
}

int main(){
    test_empty(str_init());
    std::cout << "-----------------------" << std::endl;
    ::string** arr = str_create(6);
    print_str(arr, 6);
    std::cout << "-----------------------" << std::endl;
    test_get(arr, 6, 15);
    std::cout << "-----------------------" << std::endl;
    test_plus(arr, 6, 15);
    std::cout << "-----------------------" << std::endl;
    test_compare(arr, 6, 15);
    std::cout << "-----------------------" << std::endl;
    test_copy(arr, 6);
    std::cout << "-----------------------" << std::endl;
    test_find(arr, 6, 10);
    return 0;
}
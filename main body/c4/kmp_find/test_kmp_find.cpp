//
// Created by Lenovo on 2022/4/29.
//
#include "kmp_find.h"
#define LEN 15

::string** str_create(int num){
    ::string** str_arr = (::string**)malloc(sizeof(::string*) * num);
    for (int i = 0; i < num; ++i) {
        str_arr[i] = str_init(rand_range(0, LEN));
        for (int j = 0; j < str_length(str_arr[i]); ++j) {
            str_set(str_arr[i], j + 1, rand_alpha('a', 'c'));
        }
    }
    return str_arr;
}

void print_pm(::string* ptn, int* pm){
    std::cout << "[";
    for (int i = 0; i < str_length(ptn); ++i) {
        std::cout << pm[i + 1] << ", ";
    }
    std::cout << "]";
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
        std::cout << "pm body: ";
        print_pm(ptn, kmp_pm(ptn));
        std::cout << std::endl;
        std::cout << "find: " << kmp_find(src, ptn) << std::endl;
    }
}

int main(){
    ::string* s1 = str_init("abcac");
    print_pm(s1, kmp_pm(s1));
    ::string* s2 = str_init("abaabcaba");
    print_pm(s2, kmp_pm(s2));
    std::cout << std::endl;
    print_separate();
    ::string** arr = str_create(10);
    test_find(arr, 10, 15);
    return 0;
}
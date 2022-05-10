//
// Created by Lenovo on 2022/4/30.
//
#include <cstdarg>
#include "sort.h"

typedef void (*func_sort_int)(array<int>, int);
typedef void (*func_sort_char)(array<char*>, int);
void SORT(func_sort_int sort, array<int> arr, int key){
    sort(arr, key);
}

void SORT(func_sort_char sort, array<char*> arr, int key){
    sort(arr, key);
}

array<int> array_create(int size){
    array<int> arr = array<int>(size);
    for (int i = 0; i < arr.size(); ++i) {
        arr.set(i, rand_range(0, size));
    }
    return arr;
}

array<char*> array_create(int size, int digits){
    array<char*> arr = array<char*>(size);
    for (int i = 0; i < arr.size(); ++i) {
        arr.set(i, rand_num_s(digits));
    }
    return arr;
}

void test_sort(func_sort_int func, int size, int key){
    array<int> arr = array_create(size);
    std::cout << "before: ";
    arr.print();
    std::cout << std::endl;
    SORT(func, arr, key);
    std::cout << "after: ";
    arr.print();
    std::cout << std::endl;
}

void test_sort(func_sort_char func, int size, int key, int digits){
    array<char*> arr = array_create(size, digits);
    std::cout << "before: ";
    arr.print();
    std::cout << std::endl;
    SORT(func, arr, key);
    std::cout << "after: ";
    arr.print();
    std::cout << std::endl;
}

int main(){
    test_sort(bubble_sort, 20, 0);
    test_sort(bubble_sort, 20, 1);
    print_separate();
    test_sort(select_sort, 20, 0);
    test_sort(select_sort, 20, 1);
    print_separate();
    test_sort(insert_sort, 30, 0);
    test_sort(insert_sort, 30, 1);
    print_separate();
    test_sort(shell_sort, 40, 1);
    test_sort(shell_sort, 40, 0);
    print_separate();
    test_sort(quick_sort, 60, 1);
    test_sort(quick_sort, 60, 0);
    print_separate();
    test_sort(merge_sort, 30, 0);
    test_sort(merge_sort, 30, 1);
    print_separate();
    test_sort(heap_sort, 20, 1);
    test_sort(heap_sort, 20, 0);
    print_separate();
    test_sort(radix_sort, 30, 1, 2);
    test_sort(radix_sort, 30, 0, 2);
    return 0;
}
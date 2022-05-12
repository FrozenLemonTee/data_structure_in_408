//
// Created by Lenovo on 2022/5/11.
//
#include "ordered_heap.h"
#define MAX_SIZE 50

// flag为1，输出提示信息；flag为0，不输出提示信息
ordered_heap<int>* heap_create(bool type, int size, int flag){
    array<int> arr = array<int>(size);
    for (int i = 0; i < size; ++i) {
        arr.set(i, rand_range(0, i));
    }
    ordered_heap<int>* heap = heap_init<int>(type, &arr);
    if (flag){
        heap_print(heap);
        std::cout << std::endl;
    }
    return heap;
}

void test_pop(ordered_heap<int>* heap, int num){
    for (int i = 0; i < num; ++i) {
        std::cout << "before: " << std::endl;
        heap_print(heap);
        std::cout << std::endl;
        int e = heap_pop(heap);
        std::cout << "pop: " << e << std::endl;
        std::cout << "after: " << std::endl;
        heap_print(heap);
        std::cout << std::endl;
    }
}

void test_add(ordered_heap<int>* heap, int num){
    for (int i = 0; i < num; ++i) {
        std::cout << "before: " << std::endl;
        heap_print(heap);
        std::cout << std::endl;
        std::cout << "add: ";
        int e = rand_range(0, heap->size);
        std::cout << e << std::endl;
        heap_add(heap, e);
        std::cout << "after: " << std::endl;
        heap_print(heap);
        std::cout << std::endl;
    }
}

int main(){
    ordered_heap<int>* heap1 = heap_create(MAX_HEAP, MAX_SIZE, 1);
    test_pop(heap1, MAX_SIZE);
    ordered_heap<int>* heap2 = heap_init<int>(MIN_HEAP, MAX_SIZE);
    print_separate();
    test_add(heap2, 0.4 * MAX_SIZE);
    return 0;
}
//
// Created by Lenovo on 2022/4/30.
//

#ifndef C_C___SORT_H
#define C_C___SORT_H

#endif //C_C___SORT_H
#include "global.h"

// key:为0时升序，为1时降序
T bool higher_priority(TYPE a, TYPE b, int key){
    if (!key){
        return a < b;
    }
    return a > b;
}

T void bubble_sort(array<TYPE> arr, int key){
    for (int i = 0; i < arr.size(); ++i) {
        for (int j = 0; j < arr.size() - 1 - i; ++j) {
            if (higher_priority(arr.get(j + 1), arr.get(j), key)){
                arr.exchange(j, j + 1);
            }
        }
    }
}
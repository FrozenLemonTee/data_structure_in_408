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

// 冒泡排序
T void bubble_sort(array<TYPE> arr, int key){
    for (int i = 0; i < arr.size(); ++i) {
        for (int j = 0; j < arr.size() - 1 - i; ++j) {
            if (higher_priority(arr.get(j + 1), arr.get(j), key)){
                arr.exchange(j, j + 1);
            }
        }
    }
}

// 选择排序
T void select_sort(array<TYPE> arr, int key){
    for (int i = 0; i < arr.size(); ++i) {
        int index = i;
        for (int j = i + 1; j < arr.size(); ++j) {
            if (higher_priority(arr.get(j), arr.get(index), key)){
                index = j;
            }
        }
        arr.exchange(index, i);
    }
}

// 插入类排序内部模板
T void distance_insert(array<TYPE> arr, int distance, int key){
    for (int i = 0; i < arr.size() - distance; i += distance) {
        for (int j = i; j >= 0; j -= distance) {
            if (higher_priority(arr.get(j + distance), arr.get(j), key)){
                arr.exchange(j, j + distance);
            }
        }
    }
}

// 简单插入排序
T void insert_sort(array<TYPE> arr, int key){
    distance_insert(arr, 1, key);
}

// 希尔插入排序
T void shell_sort(array<TYPE> arr, int key){
    for (int i = arr.size() / 2; i > 0; i /= 2) {
        distance_insert(arr, i, key);
    }
}

// 快速排序区间分块
T int partition(array<TYPE> arr, int l_bound, int r_bound, int key){
    int ori = rand_range(l_bound, r_bound - l_bound);
    TYPE tmp = arr.get(ori);
    arr.exchange(l_bound, ori);
    int left = l_bound;
    int right = r_bound;
    int order = -1;
    while (left < right){
        if (order == -1){
            if (higher_priority(arr.get(right), tmp, key)){
                arr.exchange(left, right);
                order = 1;
            } else{
                right -= 1;
            }
        } else{
            if (higher_priority(tmp, arr.get(left), key)){
                arr.exchange(left, right);
                order = -1;
            } else{
                left += 1;
            }
        }
    }
    arr.set(left, tmp);
    return left;
}

// 快速排序主程序
T void _quick_sort(array<TYPE> arr, int l_bound, int r_bound, int key){
    if (l_bound < r_bound){
        int mid = partition(arr, l_bound, r_bound, key);
        _quick_sort(arr, l_bound, mid - 1, key);
        _quick_sort(arr, mid + 1, r_bound, key);
    }
}

// 快速排序
T void quick_sort(array<TYPE> arr, int key){
    _quick_sort(arr, 0, arr.size() - 1, key);
}
//
// Created by Lenovo on 2022/4/30.
//

#ifndef C_C___SORT_H
#define C_C___SORT_H

#include <main body/c2/linked_list/linked_list.h>

// key为0时为升序模式，为1时为降序模式
T bool higher_priority(TYPE a, TYPE b, int key){
    if (!key){
        return a < b;
    }
    return a > b;
}

// 选择排序
T void select_sort(array<TYPE> arr, int key = 0){
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
T void distance_insert(array<TYPE> arr, int distance, int key = 0){
    for (int i = 0; i < arr.size() - distance; i += distance) {
        for (int j = i; j >= 0; j -= distance) {
            if (higher_priority(arr.get(j + distance), arr.get(j), key)){
                arr.exchange(j, j + distance);
            }
        }
    }
}

// 简单插入排序
T void insert_sort(array<TYPE> arr, int key = 0){
    distance_insert(arr, 1, key);
}

// 希尔插入排序
T void shell_sort(array<TYPE> arr, int key = 0){
    for (int i = arr.size() / 2; i > 0; i /= 2) {
        distance_insert(arr, i, key);
    }
}

// 快速排序区间分块
T int partition(array<TYPE> arr, int l_bound, int r_bound, int key = 0){
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

// 快速排序主函数
T void _quick_sort(array<TYPE> arr, int l_bound, int r_bound, int key = 0){
    if (l_bound < r_bound){
        int mid = partition(arr, l_bound, r_bound, key);
        _quick_sort(arr, l_bound, mid - 1, key);
        _quick_sort(arr, mid + 1, r_bound, key);
    }
}

// 快速排序
T void quick_sort(array<TYPE> arr, int key = 0){
    _quick_sort(arr, 0, arr.size() - 1, key);
}

// 冒泡排序
T void bubble_sort(array<TYPE> arr, int key = 0){
    for (int i = 0; i < arr.size(); ++i) {
        for (int j = 0; j < arr.size() - 1 - i; ++j) {
            if (higher_priority(arr.get(j + 1), arr.get(j), key)){
                arr.exchange(j, j + 1);
            }
        }
    }
}

// 归并排序主函数
T void _merge_sort(array<TYPE> arr, int l_bound, int r_bound, int key = 0){
    if (r_bound - l_bound > 1){
        int mid = (l_bound + r_bound) / 2;
        _merge_sort(arr, l_bound, mid, key);
        _merge_sort(arr, mid, r_bound, key);
        TYPE tmp[r_bound - l_bound];
        int cur_l = l_bound;
        int cur_r = mid;
        int cur_t = 0;
        while (mid - cur_l && r_bound - cur_r){
            if (higher_priority(arr.get(cur_l), arr.get(cur_r), key)){
                tmp[cur_t] = arr.get(cur_l);
                cur_l += 1;
            } else{
                tmp[cur_t] = arr.get(cur_r);
                cur_r += 1;
            }
            cur_t += 1;
        }
        while (mid - cur_l){
            tmp[cur_t] = arr.get(cur_l);
            cur_l += 1;
            cur_t += 1;
        }
        while (r_bound - cur_r){
            tmp[cur_t] = arr.get(cur_r);
            cur_r += 1;
            cur_t += 1;
        }
        for (int i = 0; i < r_bound - l_bound; ++i) {
            arr.set(l_bound + i, tmp[i]);
        }
    }
}

// 归并排序
T void merge_sort(array<TYPE> arr, int key = 0){
    _merge_sort(arr, 0, arr.size(), key);
}

// 获取子节点中优先级最大的节点的序号
T int get_prior_node(array<TYPE> arr, int parent, int range, int key = 0){
    if (parent * 2 + 1 <= range){
        return higher_priority(arr.get(parent * 2 - 1), arr.get(parent * 2), key) ? parent * 2 : parent * 2 + 1;
    }
    return parent * 2;
}

// 堆排序下沉操作
T void down(array<TYPE> arr, int order, int range, int key = 0){
    int cur = order;
    while (cur * 2 <= range){
        int child = get_prior_node(arr, cur, range, key);
        if (higher_priority(arr.get(cur - 1), arr.get(child - 1), key)){
            break;
        } else{
            arr.exchange(cur - 1, child - 1);
            cur = child;
        }
    }
}

// 堆排序
T void heap_sort(array<TYPE> arr, int key = 0){
    for (int i = arr.size() / 2; i > 0; --i) {
        down(arr, i, arr.size(), !key);
    }
    for (int i = arr.size(); i > 1; --i) {
        arr.exchange(0, i - 1);
        down(arr, 1, i - 1, !key);
    }
}

// 建桶操作
array<linked_list<char*>*> buckets_build(){
    array<linked_list<char*>*> buckets = array<linked_list<char*>*>(10);
    for (int i = 0; i < buckets.size(); ++i) {
        buckets.set(i, list_init<char*>());
    }
    return buckets;
}

// 基数排序
void radix_sort(array<char*> arr, int key = 0){
    int len = char_length(arr.get(0));
    array<linked_list<char*>*> buckets = buckets_build();
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < arr.size(); ++j) {
            int index = key ? 9 - (arr.get(j)[len - 1 - i] - '0') : arr.get(j)[len - 1 - i] - '0';
            list_insert(buckets.get(index), arr.get(j));
        }
        int cnt = 0;
        for (int k = 0; k < buckets.size(); ++k) {
            while (list_length(buckets.get(k))){
                arr.set(cnt, list_pop(buckets.get(k)));
                cnt += 1;
            }
        }
    }
}

#endif //C_C___SORT_H
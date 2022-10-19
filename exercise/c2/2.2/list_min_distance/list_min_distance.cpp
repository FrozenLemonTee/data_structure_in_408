//
// Created by Lenovo on 2022/10/18.
//

#include "global.h"


// 2023 2.2 14.[2020]
// 1) 算法的基本设计思想:每次固定三元组两个值，前两个值采用逐个遍历的方法，第三个值采用二分查找，
//    查找距离当前区间两端点元素之中点元素最小的元素位置，同时维护一个res变量，
//    每次计算取之前计算的三者最小距离和与当前计算值的较小者。
// 2) 算法实现如下。
// 3) 前两个值采用逐个遍历的方法，时间复杂度为o(n^2)，第三个值采用二分查找,时间复杂度为o(log(n))，
//    因此总的时间复杂度为 o(n^2*log(n))。
//    由于占用空间与长度n无关，因此总的空间复杂度为 o(1)。

// 计算三元组距离
int distance(int a, int b, int c){
    return abs(a - b) + abs(b - c) + abs(c -a);
}

// 二分查找
int bin_search(array<int> arr, int val){
    int low = 0;
    int high = arr.size() - 1;
    int mid = (low + high) / 2;
    while (low <= high){
        mid = (low + high) / 2;
        if (arr.get(mid) == val){
            return mid;
        } else if (arr.get(mid) > val){
            high = mid - 1;
        } else{
            low = mid + 1;
        }
    }
    return mid;
}

int list_min_distance(array<int> ra, array<int> rb, array<int> rc){
    int res = INT_MAX;
    for (int i = bin_search(ra, 1); i < ra.size(); ++i) { // 找到有序数组中最小正整数元素的位置
        for (int j = bin_search(rb, 1); j < rb.size(); ++j) { // 同上
            // 找到距离当前区间两端点元素之中点元素最小的元素位置，计算三元组距离以后更新res
            res = min(res,
                      distance(ra.get(i), rb.get(j),
                               rc.get(bin_search(rc, (ra.get(i) + rb.get(j)) / 2))));
        }
    }
    return res;
}

#define LEN 15

void show(array<int> ra, array<int> rb, array<int> rc){
    std::cout << "ra: ";
    ra.print(true);
    std::cout << "rb: ";
    rb.print(true);
    std::cout << "rc: ";
    rc.print(true);
    std::cout << "min_distance: " << list_min_distance(ra, rb, rc) << std::endl;
}

int main(){
    show(array<int>({-1, 0, 9}),
         array<int>({-25, -10, 10, 11}), array<int>({2, 9, 17, 30, 41}));
    return 0;
}
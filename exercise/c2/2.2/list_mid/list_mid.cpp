//
// Created by Lenovo on 2022/10/17.
//
#include "global.h"
#include "main body/c8/sort/sort.h"

// 2023 2.2 11.[2011]

// 1) 算法的基本设计思想:由两个数组长可以求得中位数位置mid = (arr1.size + arr2.size) / 2 - 1，
//    用数组top[2]分别储存指向两个数组的指针，每次比较两指针指向元素的值，使值较小者的指针向前移动，
//    同时pointer不断自增1，直到等于mid时结束循环，则arr1[top[0] - 1]和arr2[top[1] - 1]两者中较小的即为两个序列的中位数。
// 2) 算法实现如下。
// 3) 由于总共进行n次移动，每次移动操作与长度n无关，为o(1)，因此总的时间复杂度为 o(n)。由于占用空间与长度n无关，
//    因此总的空间复杂度为 o(1)。

int list_mid(array<int> arr1, array<int> arr2){
    int top[2] = {0, 0};
    int flag;
    int mid = (arr1.size() + arr2.size()) / 2 - 1;
    int val;
    for (int pointer = 0; pointer <= mid; ++pointer) {
        if (top[0] < arr1.size() && top[1] < arr2.size()){
            flag = arr2.get(top[1]) > arr1.get(top[0]);
            val = flag ? arr1.get(top[0]) : arr2.get(top[1]);
            top[!flag] += 1;
        } else if (top[0] >= arr1.size()){
            val = arr2.get(top[1]);
            top[1] += 1;
        }else{
            val = arr1.get(top[0]);
            top[0] += 1;
        }
    }
    return val;
}

#define LEN 20

void test(int cnt){
    for (int i = 0; i < cnt; ++i) {
        array<int>* arr = (array<int>*) malloc(sizeof(array<int>) * 2);
        for (int j = 0; j < 2; ++j) {
            arr[j] = array<int>(rand_range(1, LEN));
            for (int k = 0; k < arr[j].size(); ++k) {
                arr[j].set(k, rand_range(0, LEN));
            }
            quick_sort(arr[j]);
            std::cout << "arr" << j + 1 << ": ";
            arr[j].print(true);
        }
        std::cout << "mid_pos: " << (arr[0].size() + arr[1].size()) / 2 << std::endl;
        std::cout << "mid_val: " << list_mid(arr[0], arr[1]) << std::endl;
    }
}

int main(){

    test(LEN);
    return 0;
}
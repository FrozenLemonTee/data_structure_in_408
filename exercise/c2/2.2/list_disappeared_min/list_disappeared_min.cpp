//
// Created by Lenovo on 2022/10/18.
//

#include "global.h"
#include "main body/c8/sort/sort.h"


// 2023 2.2 13.[2018]

// 1) 算法的基本设计思想:将数组内元素排好序，用一个变量val维护当前指向的最小的缺失元素（初始为1），然后遍历数组:
//    若当前元素等于val，则说明val没有缺失，假定缺失的是val+1，因此将val自增1；若当前元素比val大，
//    由于数组有序，因此肯定val缺失，输出val即可；若当前元素比val小，则跳过。
// 2) 算法实现如下。
// 3) 由于预先进行了排序，时间复杂度为o(n*log(n))，而遍历数组的时间复杂度为o(n)，因此总的时间复杂度为 o(n*log(n))。
//    由于占用空间与长度n无关，因此总的空间复杂度为 o(1)。

int list_disappeared_min(array<int> arr){
    quick_sort(arr);
    int val = 1;
    for (int i = 0; i < arr.size(); ++i) {
        if (arr.get(i) == val){
            val = arr.get(i) + 1;
        } else if (arr.get(i) > val){
            return val;
        }
    }
    return val;
}

#define LEN 15

void show(array<int> arr){
    std::cout << "arr: ";
    arr.print(true);
    std::cout << "disappeared_min: " << list_disappeared_min(arr) << std::endl;
}

int main(){
    show(array<int>({-5,3,2,3}));
    show(array<int>({1,2,3}));
    show(array<int>({-5,-3,8,2,1,4,6,5,2,3,7,4}));
    show(array<int>({-4,-2,0,2,1,1,5,5,2,3,7,4}));
    return 0;
}
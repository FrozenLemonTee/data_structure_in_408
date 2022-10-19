//
// Created by Lenovo on 2022/10/18.
//

#include "global.h"

// 2023 2.2 12.[2013]

// 1) 算法的基本设计思想:创建一个大小为n的辅助数组cnt，采用直接定址法，每遍历到原数组一个元素val便将辅助数组中的cnt[val]自增1，
//    同时维护一个指针main_val指向cnt[main_val]，每当当前元素val的次数更新，
//    就通过cnt[main_val] > cnt[val] ? main_val : val指向当前统计次数最多的元素，
//    遍历完数组时，若cnt[main_val] > arr.size() / 2，输出main_val即可，否则输出-1
// 2) 算法实现如下。
// 3) 由于总共进行n次移动，每次移动操作与长度n无关，为o(1)，因此总的时间复杂度为 o(n)。由于占用空间与长度n相关，
//    因此总的空间复杂度为 o(n)。

int list_main_val(array<int> arr){
    int main_val = 0;
    int cnt[arr.size()];
    for (int i = 0; i < arr.size(); ++i) {
        cnt[i] = 0;
    }
    for (int i = 0; i < arr.size(); ++i) {
        cnt[arr.get(i)] += 1;
        main_val = cnt[main_val] > cnt[arr.get(i)] ? main_val : arr.get(i);
    }
    return cnt[main_val] > (arr.size() / 2) ? main_val : -1;
}

#define LEN 20

void show(array<int> arr){
    std::cout << "arr: ";
    arr.print(true);
    std::cout << "main_val: " << list_main_val(arr) << std::endl;
}

void test(int cnt){
    for (int i = 0; i < cnt; ++i) {
        array<int> arr = array<int>(rand_range(1, LEN * 2));
        for (int j = 0; j < arr.size(); ++j) {
            arr.set(j, rand_range(0, arr.size()));
        }
        show(arr);
    }
}

int main(){
    test(LEN);
    show(array<int>({1, 1, 2, 4, 4, 4, 5, 4, 4, 5, 2, 4, 4, 4, 4, 1, 3}));
    return 0;
}
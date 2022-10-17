//
// Created by Lenovo on 2022/10/17.
//
#include "global.h"

// 2023 2.2 09.
void list_find_and_insert(array<int> arr, int cnt, int e){
    int low = 0;
    int high = cnt - 1;
    int mid = (low + high) / 2;
    bool find = false;
    while (low <= high){
        mid = (low + high) / 2;
        if (e == arr.get(mid)){
            find = true;
            if (mid < cnt - 1){
                arr.exchange(mid, mid + 1);
            }
            break;
        } else if (e < arr.get(mid)){
            high = mid - 1;
        } else{
            low = mid + 1;
        }
    }
    if (!find){
        if (e > arr.get(mid)){
            mid += 1;
        }
        for (int i = 0; i <= cnt - mid - 1; ++i) {
            arr.set(cnt - i, arr.get(cnt - i - 1));
        }
        arr.set(mid, e);
    }
}

#define LEN 30

void test(int cnt){
    for (int i = 0; i < cnt; ++i) {
        array<int> arr = array<int>(LEN);
        int amount = rand_range(0, LEN * 0.8);
        while (!amount){
            amount = rand_range(0, LEN * 0.8);
        }
        int val = rand_range(0, LEN);
        for (int j = 0; j < amount; ++j) {
            arr.set(j, val);
            val = rand_range(val + 1, LEN);
        }
        std::cout << "before: ";
        arr.print(true);
        int elem = rand_range(0, LEN);
        std::cout << "find: " << elem << std::endl;
        list_find_and_insert(arr, amount, elem);
        std::cout << "after: ";
        arr.print(true);
    }
}

int main(){
    test(LEN);
    return 0;
}
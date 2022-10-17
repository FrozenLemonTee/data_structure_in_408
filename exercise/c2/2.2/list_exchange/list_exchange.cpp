//
// Created by Lenovo on 2022/10/13.
//

#include "global.h"

// 2023 2.2 08.
void list_exchange(array<int> arr, int bound){
    array<int> tmp = join(arr, bound, arr.size(), arr, 0, bound);
    for (int i = 0; i < arr.size(); ++i) {
        arr.set(i, tmp.get(i));
    }
}

#define LEN 30

void test(int cnt){
    for (int i = 0; i < cnt; ++i) {
        array<int> list = array<int>(LEN * 0.5);
        for (int j = 0; j < list.size(); ++j) {
            list.set(j, rand_range(0, LEN));
        }
        int bound = rand_range(0, list.size());
        std::cout << "bound: " << bound <<std::endl;
        std::cout << "before: ";
        list.print(true);
        list_exchange(list, bound);
        std::cout << "after: ";
        list.print(true);
    }
}

int main(){
    test(LEN);
    return 0;
}
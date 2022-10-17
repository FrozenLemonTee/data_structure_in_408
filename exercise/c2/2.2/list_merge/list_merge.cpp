//
// Created by Lenovo on 2022/10/13.
//

#include "main body/c8/sort/sort.h"

// 2023 2.2 07.
array<int> list_merge(array<int> list1, array<int> list2){
    array<int> list = array<int>(list1.size() + list2.size());
    int p[3] = {0, 0, 0};
    while (p[0] < list1.size() && p[1] < list2.size()){
        bool pri = list1.get(p[0]) > list2.get(p[1]);
        list.set(p[2], pri ? list2.get(p[1]) : list1.get(p[0]));
        p[pri] += 1;
        p[2] += 1;
    }
    while (p[0] < list1.size()){
        list.set(p[2], list1.get(p[0]));
        p[0] += 1;
        p[2] += 1;
    }
    while (p[1] < list2.size()){
        list.set(p[2], list2.get(p[1]));
        p[1] += 1;
        p[2] += 1;
    }
    return list;
}

#define LEN 20

void test(int cnt){
    for (int i = 0; i < cnt; ++i) {
        array<int>* list = (array<int>*) malloc(sizeof(array<int>) * 2);
        std::cout << "before:" << std::endl;
        for (int j = 0; j < 2; ++j) {
            list[j] = array<int>(rand_range(0, LEN * 2));
            for (int k = 0; k < list[j].size(); ++k) {
                list[j].set(k, rand_range(0, 5 * LEN));
            }
            quick_sort(list[j]);
            list[j].print(true);
        }
        array<int> arr = list_merge(list[0], list[1]);
        std::cout << "after:" << std::endl;
        arr.print(true);
    }
}

int main(){
    test(LEN);
    return 0;
}
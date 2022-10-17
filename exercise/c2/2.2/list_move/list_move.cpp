//
// Created by Lenovo on 2022/10/17.
//
#include "global.h"

// 2023 2.2 10.[2010]

// 1) 算法的基本设计思想:从最后一个元素开始，每次将当前位置pointer的值复制到(pointer - p + n) % n的位置（复制前用变量tmp暂存），
//    每操作一次，count的值加一（初值为0），同时检查pointer的位置是否回到初始的位置，若回到初始位置，向前移动1个下标，并重复上述操作，
//    直到count == n时结束。
// 2) 算法实现如下。
// 3) 由于总共进行n次移动，每次移动操作与长度n无关，为o(1)，因此总的时间复杂度为 o(n)。由于占用空间与长度n无关，
//    因此总的空间复杂度为 o(1)。
void change(array<int> arr, int index, int &cur){
    int tmp = cur;
    cur = arr.get(index);
    arr.set(index, tmp);
}

void list_move(array<int> arr, int move){
    int count = 0;
    for (int i = arr.size() - 1; i >= 0; --i) {
        int cur = arr.get(i);
        int pointer = (i - move + arr.size()) % arr.size();
        while (pointer != i){
            if (count == arr.size()){
                return;
            }
            change(arr, pointer, cur);
            pointer = (pointer - move + arr.size()) % arr.size();
            count += 1;
        }
        if (count == arr.size()){
            return;
        }
        change(arr, pointer, cur);
        count += 1;
    }
}

#define LEN 20

void test(int cnt){
    for (int i = 0; i < cnt; ++i) {
        array<int> arr = array<int>(rand_range(1, LEN + 1));
        for (int j = 0; j < arr.size(); ++j) {
            arr.set(j, rand_range(0, 2 * LEN));
        }
        std::cout << "before: ";
        arr.print(true);
        int move = rand_range(1, arr.size() - 1);
        std::cout << "move: " << move << std::endl;
        list_move(arr, move);
        std::cout << "after: ";
        arr.print(true);
    }
}

int main(){

    test(LEN * 0.5);
    return 0;
}
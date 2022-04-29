#include <iostream>
#include "cmath"

#ifndef C_C___GLOBAL_H
#define C_C___GLOBAL_H

#endif //C_C___GLOBAL_H
#define T template<typename TYPE>
void error(const char* err_msg, int err_code);

#define ILLEGAL_INDEX error("Illegal index", 100)
#define INSERT_ERROR error("Can not insert element", 101)
#define POP_ERROR error("Can not pop element", 102)
#define ILLEGAL_SUFFIX error("Illegal suffix", 103)
#define TYPE_ERROR error("wrong usage of the element", 104)


// 定义异常显示
void error(const char* err_msg, int err_code){
    std::cerr << std::endl << err_msg << std::endl;
    exit(err_code);
}

// 生成指定范围内的随机整数
int rand_range(int start, int range){
    return range ? start + rand() % range : start;
}

// 随机生成布尔值
bool rand_bool(){
    return rand_range(0, 2);
}

// 生成0到1之间的浮点数
double rand_double(){
    return (double)(rand() % 101) / 101;
}

// 生成任意字母
char rand_alpha(){
    if (rand_bool()){
        return rand_range('a', 'z' - 'a');
    }
    return rand_range('A', 'Z' - 'A');
}

// 交换两个变量的值
T void swap(TYPE &a, TYPE &b){
    TYPE tmp = a;
    a = b;
    b = tmp;
}

// 返回两者中的较小值
T TYPE min(TYPE a, TYPE b){
    return a < b ? a : b;
}

// 返回两者中的较大值
T TYPE max(TYPE a, TYPE b){
    return a > b ? a : b;
}
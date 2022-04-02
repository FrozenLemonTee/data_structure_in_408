#include <iostream>

#ifndef C_C___GLOBAL_H
#define C_C___GLOBAL_H

#endif //C_C___GLOBAL_H


// 定义异常显示
void error(const char* err_msg, int err_code){
    std::cerr << std::endl << err_msg << std::endl;
    exit(err_code);
}

// 生成指定范围内的随机整数
int rand_range(int range_a, int range_b){
    return range_b ? range_a + rand() % range_b : range_a;
}
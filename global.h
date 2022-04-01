//
// Created by Lenovo on 2022/4/1.
//

#ifndef C_C___GLOBAL_H
#define C_C___GLOBAL_H

#include <iostream>

// 定义异常显示
void error(const char* err_msg, int err_code){
    std::cerr << err_msg << std::endl;
    exit(err_code);
}
#endif //C_C___GLOBAL_H
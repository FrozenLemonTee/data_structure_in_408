#include <iostream>

// 定义异常显示
void error(const char* err_msg, int err_code){
    std::cerr << err_msg << std::endl;
    exit(err_code);
}
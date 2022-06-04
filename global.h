#include <iostream>
#include "cstring"
#include "cmath"

#ifndef C_C___GLOBAL_H
#define C_C___GLOBAL_H

#endif //C_C___GLOBAL_H
#define T template<typename TYPE> // 定义模板参数
void error(const char* err_msg, int err_code);
T void swap(TYPE &a, TYPE &b);

// 常用异常定义

#define ILLEGAL_INDEX error("Illegal index", 100) // 非法索引异常
#define INSERT_ERROR error("Can not insert element", 101) // 元素插入异常
#define POP_ERROR error("Can not pop element", 102) // 元素弹出异常
#define ILLEGAL_SUFFIX error("Illegal suffix", 103) // 非法下标（编号）异常
#define TYPE_ERROR error("wrong usage of the element", 104) // 类型异常
#define NULL_PTR error("given a null pointer", 105) // 空指针异常
#define GRAPH_SIDE_ERROR error("wrong setting in graph", 106) // 图边设置异常


// 数组定义
T struct array{
private:
    TYPE* body;
    int cnt;

    bool check_index(int index){
        return index >= 0 && index < this->cnt;
    }
public:
    array(int size){
        this->cnt = size;
        this->body = (TYPE*)malloc(sizeof(TYPE) * size);
    }

    int size(){
        return this->cnt;
    }

    TYPE get(int index){
        if (!this->check_index(index)){
            ILLEGAL_INDEX;
        }
        return this->body[index];
    }

    void set(int index, TYPE elem){
        if (!this->check_index(index)){
            ILLEGAL_INDEX;
        }
        this->body[index] = elem;
    }

    void exchange(int index1, int index2){
        if (!this->check_index(index1) || !this->check_index(index2)){
            ILLEGAL_INDEX;
        }
        swap(this->body[index1], this->body[index2]);
    }

    void print(){
        std::cout << "[";
        for (int i = 0; i < this->size(); ++i) {
            std::cout << this->body[i] << ", ";
        }
        std::cout << "]";
    }
};

// 打印分隔线
void print_separate(){
    std::cout << "-----------------------" << std::endl;
}

// 计算字符串的长度
int char_length(const char* s){
    int cnt = 0;
    while (s[cnt] != '\0'){
        cnt += 1;
    }
    return cnt;
}

// 定义异常显示
void error(const char* err_msg, int err_code){
    std::cerr << std::endl << err_msg << std::endl;
    exit(err_code);
}

// 返回两者中的较大值
T TYPE max(TYPE a, TYPE b){
    return a > b ? a : b;
}

// 返回两者中的较小值
T TYPE min(TYPE a, TYPE b){
    return a < b ? a : b;
}

// 直接交换两个变量的值
T void swap(TYPE &a, TYPE &b){
    TYPE tmp = a;
    a = b;
    b = tmp;
}

// 根据索引交换线性结构中两元素的值
T void swap(TYPE* p, int index1, int index2){
    TYPE tmp = *(p + index1);
    *(p + index1) = *(p + index2);
    *(p + index2) = tmp;
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

// 生成两个字母间的任意字母
char rand_alpha(char a, char b){
    if (islower(a)){
        return rand_range(tolower(min(a, b)), (abs(a - tolower(b))) % 26 + 1);
    }
    return rand_range(toupper(min(a, b)), (abs(a - toupper(b))) % 26 + 1);
}

// 在整型范围内生成任意位数的自然数
int rand_num(int digits){
    int res = 0;
    int radix = 1;
    for (int i = 0; i < digits; ++i) {
        res += rand_range(0, 10) * radix;
        radix *= 10;
    }
    return res;
}

// 在整型范围内生成任意位数的自然数
char* rand_num_s(int digits){
    int num = rand_num(digits);
    char *c = (char*)malloc(sizeof(char*));
    sprintf(c, "%d", num);
    int len = char_length(c);
    char *res = (char*)malloc(sizeof(char*));
    for (int i = 0; i < digits - len; ++i) {
        res[i] = '0';
    }
    for (int i = 0; i < len; ++i) {
        res[digits - len + i] = c[i];
    }
    res[digits] = '\0';
    return res;
}
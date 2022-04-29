//
// Created by Lenovo on 2022/4/25.
//
struct string;
::string* str_init();
::string* str_init(int size);
::string* str_init(int size, char c);
::string* str_init(::string* str);
::string* str_init(::string* str, int start, int len);
::string* str_init(const char* const_str);
int str_length(::string* str);
bool str_order_check(::string* str, int order);

#ifndef C_C___MY_STRING_H
#define C_C___MY_STRING_H

#endif //C_C___MY_STRING_H
#include "global.h"

// 字符串结构定义
typedef struct string{
    char* ch_pointer; // 串体指针，0下标处储存当前字符串长度
}string;


// 返回字符串长度
int str_length(::string* str){
    return str->ch_pointer[0];
}

// 判断字符串是否为空
bool str_empty(::string* str){
    return !str->ch_pointer[0];
}

// 检查传入序号是否合法
bool str_order_check(::string* str, int order){
    return order >= 1 && order <= str_length(str);
}

// 访问字符
char str_get(::string* str, int order){
    if (!str_order_check(str, order)){
        ILLEGAL_INDEX;
    }
    return str->ch_pointer[order];
}

// 修改字符
void str_set(::string* str, int order, char c){
    if (!str_order_check(str, order)){
        ILLEGAL_INDEX;
    }
    str->ch_pointer[order] = c;
}

// 无参数传入的字符串构造方法，初始长度为0
::string* str_init(){
    return str_init(0);
}

// 传入长度参数的字符串构造方法
::string* str_init(int size, char c){
    ::string* str = (::string*)malloc(sizeof(::string));
    str->ch_pointer = (char*)malloc(sizeof(char) * (size + 1));
    for (int i = 0; i < size; ++i) {
        str->ch_pointer[i + 1] = c;
    }
    str->ch_pointer[0] = size;
    return str;
}

// 默认以NULL填充的字符串构造方法
::string* str_init(int size){
    return str_init(size, 0);
}

// 传入另一个字符串部分区间的字符串构造方法
::string* str_init(::string* str, int start, int len){
    if (!str_order_check(str, start)|| !str_order_check(str, start + len - 1)){
        ILLEGAL_INDEX;
    }
    ::string* n_str = (::string*)malloc(sizeof(::string));
    n_str->ch_pointer = (char*)malloc(sizeof(char) * (len + 1));
    n_str->ch_pointer[0] = len;
    for (int i = 0; i < len; ++i) {
        n_str->ch_pointer[i + 1] = str->ch_pointer[start + i];
    }
    return n_str;
}

// 默认传入整个字符串的构造方法
::string* str_init(::string* str){
    return str_init(str, 1, str_length(str));
}

// 传入一个常量字符串的字符串构造方法
::string* str_init(const char* const_str){
    int cnt = 0;
    while (const_str[cnt] != '\0'){
        cnt += 1;
    }
    ::string* n_str = str_init(cnt);
    for (int i = 0; i < cnt; ++i) {
        n_str->ch_pointer[i + 1] = const_str[i];
    }
    return n_str;
}

// 将两个字符串拼接成新的字符串
::string* str_add(::string* str1,::string* str2){
    ::string* n_str = str_init(str_length(str1) + str_length(str2));
    for (int i = 0; i < str_length(str1); ++i) {
        n_str->ch_pointer[i + 1] = str1->ch_pointer[i + 1];
    }
    for (int i = 0; i < str_length(str2); ++i) {
        n_str->ch_pointer[i + str_length(str1) + 1] = str2->ch_pointer[i + 1];
    }
    return n_str;
}

// 按字典序比较两个字符串
int str_compare(::string* str1, ::string* str2){
    for (int j = 0; str_order_check(str1, j + 1) && str_order_check(str2, j + 1); ++j) {
        if (str1->ch_pointer[j + 1] != str2->ch_pointer[j + 1]){
            return str1->ch_pointer[j + 1] - str2->ch_pointer[j + 1];
        }
    }
    return str_length(str1) - str_length(str2);
}

// 对主串进行模式匹配
int str_find(::string* src, ::string* ptn){
    if (str_length(ptn) > str_length(src)){
        return 0;
    }
    int s = 1, p = 1;
    bool first = 0;
    while (str_order_check(src, s) && str_order_check(ptn, p)){
        if (str_get(src, s) == str_get(ptn, p)){
            first = 1;
            if (str_length(ptn) == p){
                return s - str_length(ptn) + 1;
            }
            p += 1;
            s += 1;
        } else{
            if (first){
                first = 0;
                p = 1;
            } else{
                s += 1;
            }
        }
    }
    return 0;
}

// 打印字符串
void str_print(::string* str){
    std::cout << "\"";
    for (int i = 0; i < str_length(str); ++i) {
        std::cout << str->ch_pointer[i + 1];
    }
    std::cout << "\"";
}


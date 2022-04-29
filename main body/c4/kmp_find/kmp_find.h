//
// Created by Lenovo on 2022/4/29.
//

#ifndef C_C___KMP_FIND_H
#define C_C___KMP_FIND_H

#endif //C_C___KMP_FIND_H
#include <main body/c4/my_string/my_string.h>

int* kmp_pm(::string* ptn){
    int* pm = (int*)malloc(sizeof(int) * (str_length(ptn) + 1));
    pm[0] = 0;
    int cur = 1;
    while (str_order_check(ptn, cur)){
        if (cur < 2){
            pm[cur] = 0;
        } else{
            int pre = pm[cur - 1] + 1;
            while (pre > 1 && str_get(ptn, cur) != str_get(ptn, pre)){
                pre = pm[pre - 1] + 1;
            }
            if (str_get(ptn, cur) != str_get(ptn, pre)){
                pm[cur] = 0;
            } else{
                pm[cur] = pre;
            }
        }
        cur += 1;
    }
    return pm;
}

int kmp_find(::string* src, ::string* ptn){
    if (str_length(ptn) > str_length(src)){
        return 0;
    }
    int* pm = kmp_pm(ptn);
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
                p -= p - 1 - pm[p - 1];
                first = 0;
            } else{
               s += 1;
            }
        }
    }
    return 0;
}
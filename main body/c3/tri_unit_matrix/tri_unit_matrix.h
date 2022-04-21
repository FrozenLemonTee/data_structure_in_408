//
// Created by Lenovo on 2022/4/19.
//

#ifndef C_C___TRI_UNIT_MATRIX_H
#define C_C___TRI_UNIT_MATRIX_H

#endif //C_C___TRI_UNIT_MATRIX_H
#include "global.h"

// 三元组定义
T struct tri_unit{
    TYPE val; // 三元组之数据值
    int i; // 三元组之行下标
    int j; // 三元组之列下标
};

// 三元组初始化
T tri_unit<TYPE>* tri_unit_init(TYPE val, int i, int j){
    tri_unit<TYPE>* unit = (tri_unit<TYPE>*)malloc(sizeof(tri_unit<TYPE>));
    unit->val = val;
    unit->i = i;
    unit->j = j;
    return unit;
}

// 三元组矩阵定义
T struct tri_matrix{
    tri_unit<TYPE>* matrix_body; // 矩阵体指针
    int cnt; // 当前元素个数
    int i_len; // 矩阵列数
    int j_len; // 矩阵行数
};

// 获取矩阵的最大容量
T int tri_matrix_max_size(tri_matrix<TYPE>* matrix){
    return matrix->i_len * matrix->j_len;
}

// 获取矩阵的当前元素个数
T int tri_matrix_length(tri_matrix<TYPE>* matrix){
    return matrix->cnt;
}

// 判断矩阵是否已满
T bool tri_matrix_is_full(tri_matrix<TYPE>* matrix){
    return matrix->cnt == tri_matrix_max_size(matrix);
}

// 检查该行或列下标是否合法.flag为0:行下标,flag为1:列下标
T bool tri_matrix_check_index(tri_matrix<TYPE>* matrix, int index, int flag){
    if (!flag){
        return index >= 0 && index < matrix->i_len;
    } else{
        return index >= 0 && index < matrix->j_len;
    }
}

// 三元组矩阵初始化
T tri_matrix<TYPE>* tri_matrix_init(int i_len, int j_len){
    tri_matrix<TYPE>* matrix = (tri_matrix<TYPE>*)malloc(sizeof(tri_matrix<TYPE>));
    matrix->i_len = i_len;
    matrix->j_len = j_len;
    matrix->matrix_body = (tri_unit<TYPE>*)malloc(sizeof(tri_unit<TYPE>) * tri_matrix_max_size(matrix));
    matrix->cnt = 0;
    return matrix;
}

// 通过三元组行、列下标查找在矩阵中的存储下标
T int tri_matrix_find_suffix(tri_matrix<TYPE>* matrix, int i, int j){
    if (!tri_matrix_check_index(matrix, i, 0) || !tri_matrix_check_index(matrix, j, 1)){
        ILLEGAL_INDEX;
    }
    for (int k = 0; k < tri_matrix_length(matrix); ++k) {
        tri_unit<TYPE>* cur = &matrix->matrix_body[k];
        if (cur->i == i && cur->j == j){
            return k;
        }
    }
    return -1;
}

// 通过行、列下标获取元素
T TYPE tri_matrix_get_val(tri_matrix<TYPE>* matrix, int i, int j){
    int suffix = tri_matrix_find_suffix(matrix, i, j);
    if (suffix == -1){
        ILLEGAL_SUFFIX;
    }
    return matrix->matrix_body[suffix].val;
}

// 将新元素插入矩阵中，如果插入位置已有元素，则直接覆盖
T void tri_matrix_set(tri_matrix<TYPE>* matrix, TYPE elem, int i, int j){
    if (!tri_matrix_check_index(matrix, i, 0) || !tri_matrix_check_index(matrix, j, 1)){
        ILLEGAL_INDEX;
    }
    int suffix = tri_matrix_find_suffix(matrix, i, j);
    if (suffix != -1){
        tri_unit<TYPE>* cur = &matrix->matrix_body[suffix];
        cur->val = elem;
    } else{
        if (tri_matrix_is_full(matrix)){
            INSERT_ERROR;
        }
        matrix->matrix_body[matrix->cnt] = *tri_unit_init(elem, i, j);
        matrix->cnt += 1;
    }
}

// 打印矩阵
T void tri_matrix_print(tri_matrix<TYPE>* matrix){
    for (int i = 0; i < matrix->i_len; ++i) {
        std::cout << "          ";
        std::cout << "[";
        for (int j = 0; j < matrix->j_len; ++j) {
            int suffix = tri_matrix_find_suffix(matrix, i, j);
            if (suffix == -1){
                std::cout << 0 << ", ";
                continue;
            }
            tri_unit<TYPE>* cur = &matrix->matrix_body[suffix];
            std::cout << cur->val << ", ";
        }
        std::cout << "]" << std::endl;
    }
}

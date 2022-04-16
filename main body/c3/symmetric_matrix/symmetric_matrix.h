//
// Created by Lenovo on 2022/4/16.
//

#ifndef C_C___SYMMETRIC_MATRIX_H
#define C_C___SYMMETRIC_MATRIX_H

#endif //C_C___SYMMETRIC_MATRIX_H
#include "global.h"


// 对称矩阵定义
T struct symmetric_matrix{
    TYPE* matrix_body; // 对称矩阵体指针
    int side_len; // 对称矩阵边长
};

#define symmetric_matrix symmetric_matrix<TYPE>

// 返回矩阵的总大小
T int matrix_get_size(symmetric_matrix* matrix){
    return matrix->side_len * matrix->side_len;
}

// 对称矩阵初始化
T symmetric_matrix* matrix_init(int size){
    symmetric_matrix* matrix = (symmetric_matrix*)malloc(sizeof(symmetric_matrix));
    matrix->side_len = size;
    matrix->matrix_body = (TYPE*)malloc(sizeof(TYPE)*(matrix->side_len * matrix->side_len));
    for (int i = 0; i < matrix_get_size(matrix); ++i) {
        matrix->matrix_body[i] = NULL;
    }
    return matrix;
}

// 获取矩阵的元素
T TYPE matrix_get_val(symmetric_matrix* matrix, int i, int j){
    if (j > i){
        int tmp = i;
        i = j;
        j = tmp;
    }
    return matrix->matrix_body[(1 + i) * i / 2 + j];
}

// 将元素插入到矩阵中
T void matrix_set_val(symmetric_matrix* matrix, int i, int j, TYPE val){
    if (j > i){
        int tmp = i;
        i = j;
        j = tmp;
    }
    matrix->matrix_body[(1 + i) * i / 2 + j] = val;
}

// 打印对称矩阵
T void matrix_print(symmetric_matrix* matrix){
    for (int i = 0; i < matrix->side_len; ++i) {
        std::cout << "          ";
        std::cout << "[";
        for (int j = 0; j < matrix->side_len; ++j) {
            std::cout << matrix_get_val(matrix, i, j) << ", ";
        }
        std::cout << "]" << std::endl;
    }
}
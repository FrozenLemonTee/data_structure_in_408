//
// Created by Lenovo on 2022/4/17.
//

#ifndef C_C___THREE_DIAGONALS_MATRIX_H
#define C_C___THREE_DIAGONALS_MATRIX_H

#endif //C_C___THREE_DIAGONALS_MATRIX_H
#include "global.h"


// 三对角矩阵定义
T struct three_diagonals_matrix{
    TYPE* matrix_body;
    int side_len;
};

#define three_diagonals_matrix three_diagonals_matrix<TYPE>

// 返回矩阵的总大小
T int matrix_get_size(three_diagonals_matrix* matrix){
    return 3 * matrix->side_len - 1;
}

// 初始化矩阵
T three_diagonals_matrix* matrix_init(int len, TYPE val){
    three_diagonals_matrix* matrix = (three_diagonals_matrix*)malloc(sizeof(three_diagonals_matrix));
    matrix->side_len = len;
    matrix->matrix_body = (TYPE*)malloc(sizeof(TYPE) * matrix_get_size(matrix));
    for (int i = 0; i < matrix_get_size(matrix) - 1; ++i) {
        matrix->matrix_body[i] = (TYPE)NULL;
    }
    matrix->matrix_body[matrix_get_size(matrix) - 1] = val;
    return matrix;
}

// 获取矩阵的元素
T TYPE matrix_get_val(three_diagonals_matrix* matrix, int i, int j){
    if (abs(i - j) > 1){
        return matrix->matrix_body[matrix_get_size(matrix) - 1];
    }
    return matrix->matrix_body[2 * i + j];
}

// 将元素插入到矩阵中
T void matrix_set_val(three_diagonals_matrix* matrix, int i, int j, TYPE val){
    if (abs(i - j) > 1){
        matrix->matrix_body[matrix_get_size(matrix) - 1] = val;
    }
    matrix->matrix_body[2 * i + j] = val;
}

// 打印对称矩阵
T void matrix_print(three_diagonals_matrix* matrix){
    for (int i = 0; i < matrix->side_len; ++i) {
        std::cout << "          ";
        std::cout << "[";
        for (int j = 0; j < matrix->side_len; ++j) {
            std::cout << matrix_get_val(matrix, i, j) << ", ";
        }
        std::cout << "]" << std::endl;
    }
}
//
// Created by Lenovo on 2022/4/16.
//
#include "symmetric_matrix.h"
#undef symmetric_matrix
#define LEN 5

symmetric_matrix<int>* matrix_build(int side_len){
    symmetric_matrix<int>* matrix = matrix_init<int>(side_len);
    for (int i = 0; i < matrix->side_len; ++i) {
        for (int j = 0; j < matrix->side_len; ++j) {
            matrix_set_val(matrix, i, j, rand_range(0, matrix_get_size(matrix) / 2));
        }
    }
    return matrix;
}

// flag为1，输出提示信息；flag为0，不输出提示信息
void test_set(symmetric_matrix<int>* matrix, int num, int flag){
    for (int index = 0; index < num; ++index) {
        int i = rand_range(0, matrix->side_len);
        int j = rand_range(0, matrix->side_len);
        int val = rand_range(0, matrix_get_size(matrix));
        if (flag){
            std::cout << "cur position: (" << i+1 << ", " << j+1 << "), ";
            std::cout << "cur val: " << val << std::endl;
        }
        matrix_set_val(matrix, i, j, val);
        if (flag)
        matrix_print(matrix);
    }
}

void test_get(symmetric_matrix<int>* matrix, int num){
    for (int index = 0; index < num; ++index) {
        int i = rand_range(0, matrix->side_len);
        int j = rand_range(0, matrix->side_len);
        std::cout << "cur position: (" << i+1 << ", " << j+1 << "), " << matrix_get_val(matrix, i, j) << std::endl;
    }
}

int main(){
    symmetric_matrix<int>* matrix = matrix_build(LEN);
    matrix_print(matrix);
    std::cout << "-----------------------" << std::endl;
    test_get(matrix, 10);
    std::cout << "-----------------------" << std::endl;
    test_set(matrix, 10, 1);
    return 0;
}
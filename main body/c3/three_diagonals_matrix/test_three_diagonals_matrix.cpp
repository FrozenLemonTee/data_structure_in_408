//
// Created by Lenovo on 2022/4/17.
//
#include "three_diagonals_matrix.h"
#undef three_diagonals_matrix
#define LEN 10

// 随机生成坐标
void rand_coords(three_diagonals_matrix<int>* matrix, int &i, int &j){
    i = rand_range(0, matrix->side_len);
    j = rand_range(0, matrix->side_len);
    while (abs(i - j) > 1){
        i = rand_range(0, matrix->side_len);
        j = rand_range(0, matrix->side_len);
    }
}

three_diagonals_matrix<int>* matrix_build(int side_len, int val){
    three_diagonals_matrix<int>* matrix = matrix_init<int>(side_len, val);
    for (int i = 0; i < matrix->side_len; ++i) {
        for (int j = 0; j < matrix->side_len; ++j) {
            if (abs(i - j) > 1){
                continue;
            }
            matrix_set_val(matrix, i, j, rand_range(0, matrix_get_size(matrix) / 2));
        }
    }
    return matrix;
}

// flag为1，输出提示信息；flag为0，不输出提示信息
void test_set(three_diagonals_matrix<int>* matrix, int num, int flag){
    for (int index = 0; index < num; ++index) {
        int i ,j;
        rand_coords(matrix, i, j);
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

void test_get(three_diagonals_matrix<int>* matrix, int num){
    for (int index = 0; index < num; ++index) {
        int i = rand_range(0, matrix->side_len);
        int j = rand_range(0, matrix->side_len);
        std::cout << "cur position: (" << i+1 << ", " << j+1 << "), " << matrix_get_val(matrix, i, j) << std::endl;
    }
}

int main(){
    three_diagonals_matrix<int>* matrix = matrix_build(LEN, 0);
    matrix_print(matrix);
    std::cout << "-----------------------" << std::endl;
    test_get(matrix, 10);
    std::cout << "-----------------------" << std::endl;
    test_set(matrix, 10, 1);
    return 0;
}
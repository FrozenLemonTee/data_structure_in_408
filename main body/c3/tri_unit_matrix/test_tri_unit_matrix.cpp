//
// Created by Lenovo on 2022/4/19.
//
#include "tri_unit_matrix.h"

#define LEN 10

// 随机生成坐标
void rand_coords(tri_matrix<int>* matrix, int &i, int &j){
    i = rand_range(0, matrix->i_len);
    j = rand_range(0, matrix->j_len);
}

tri_matrix<int>* matrix_build(int i_len, int j_len, int num){
    tri_matrix<int>* matrix = tri_matrix_init<int>(i_len, j_len);
    for (int i = 0; i < num; ++i) {
        int j, k;
        rand_coords(matrix, j, k);
        tri_matrix_set(matrix, rand_range(0, LEN * 2), j, k);
    }
    return matrix;
}

// flag为1，输出提示信息；flag为0，不输出提示信息
void test_set(tri_matrix<int>* matrix, int num, int flag){
    for (int index = 0; index < num; ++index) {
        int i ,j;
        rand_coords(matrix, i, j);
        int val = rand_range(0, LEN * 2);
        if (flag){
            std::cout << "cur position: (" << i+1 << ", " << j+1 << "), ";
            std::cout << "cur val: " << val << std::endl;
        }
        tri_matrix_set(matrix, val, i, j);
        if (flag)
            tri_matrix_print(matrix);
    }
}

void test_get(tri_matrix<int>* matrix, int num){
    for (int index = 0; index < num; ++index) {
        int i, j;
        rand_coords(matrix, i, j);
        if (tri_matrix_find_suffix(matrix, i, j) == -1){
            std::cout << "cur position: (" << i+1 << ", " << j+1 << "), " << 0 << std::endl;
        } else{
            std::cout << "cur position: (" << i+1 << ", " << j+1 << "), " << tri_matrix_get_val(matrix, i, j) << std::endl;
        }
    }
}

int main(){
    tri_matrix<int>* matrix = matrix_build(5, 3, 7);
    tri_matrix_print(matrix);
    std::cout << "-----------------------" << std::endl;
    test_get(matrix, 30);
    std::cout << "-----------------------" << std::endl;
    test_set(matrix, 10, 1);
    return 0;
}
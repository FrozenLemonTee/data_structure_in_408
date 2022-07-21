//
// Created by Lenovo on 2022/5/17.
//

#ifndef C_C___THREAD_TREE_H
#define C_C___THREAD_TREE_H

#endif //C_C___THREAD_TREE_H
#include "main body/c5/tree_traverse/tree_traverse.h"

#define LEFT 0
#define RIGHT 1

// 线索树节点定义
T struct thread_node{
    TYPE data; // 节点数据域
    thread_node<TYPE>* left; // 节点左指针域
    thread_node<TYPE>* right; // 节点右指针域
    bool is_child_left; // 节点左指针标志，1指示为左孩子指针，0指示为前驱
    bool is_child_right; // 节点右指针标志，1指示为右孩子指针，0指示为后驱
};

// 线索树节点初始化
T thread_node<TYPE>* r_node_init(binary_tree::tree_node<TYPE>* tree_node){
    thread_node<TYPE>* r_node = (::thread_node<TYPE>*)malloc(sizeof(::thread_node<TYPE>));
    r_node->data = tree_node->data;
    r_node->left = (::thread_node<TYPE>*)nullptr;
    r_node->right = (::thread_node<TYPE>*)nullptr;
    r_node->is_child_left = 1;
    r_node->is_child_right = 1;
    return r_node;
}

// 检查线索树节点是否为空
T bool r_node_check_null(thread_node<TYPE>* r_node){
    return !r_node;
}

// 获取节点的左右指针域
T thread_node<TYPE>* get_pointer(thread_node<TYPE>* r_node, bool pos){
    if (!pos){
        return r_node->left;
    }
    return r_node->right;
}

// 设置节点的左右指针域
T void set_pointer(thread_node<TYPE>* r_node, bool pos, thread_node<TYPE>* pointer){
    if (!pos){
        r_node->left = pointer;
    } else{
        r_node->right = pointer;
    }
}

// 打印线索树节点
T UNUSED bool r_node_print(thread_node<TYPE>* r_node){
    if (r_node_check_null(r_node)){
        NULL_PTR;
    }
    std::cout << "(#" << r_node << ", " << r_node->data << ", " << "LEFT_IS_CHILD: " <<
    r_node->is_child_left <<  ", " << "RIGHT_IS_CHILD: " << r_node->is_child_right << ")";
}

// 线索树定义
T struct thread_tree{
    thread_node<TYPE>* root; // 线索树根节点
    int cnt; // 线索树节点数量
};

// 线索化主函数
T void threaded(thread_node<TYPE>* cur, thread_node<TYPE>*& pre){
    if (!r_node_check_null(cur)){
        threaded(get_pointer(cur, LEFT), pre);
        if (r_node_check_null(get_pointer(cur, LEFT))){
            cur->left = pre;
            cur->is_child_left = 0;
        }
        if (!r_node_check_null(pre) && !r_node_check_null(get_pointer(pre, RIGHT))){
            pre->right = cur;
            pre->is_child_right = 0;
        }
        pre = cur;
        threaded(get_pointer(cur, RIGHT), pre);
    }
}

// 将二叉树拷贝成一份未线索化的线索树
T thread_tree<TYPE>* r_tree_copy(binary_tree::binary_tree<TYPE>* b_tree){
    thread_tree<TYPE>* tree = (thread_tree<TYPE>*)malloc(sizeof(thread_tree<TYPE>));
    tree->root = (thread_node<TYPE>*) nullptr;
    tree->cnt = 0;
    linked_queue::linked_queue<binary_tree::tree_node<TYPE>*>* b_nodes = linked_queue::queue_init<binary_tree::tree_node<TYPE>*>();
    linked_queue::linked_queue<thread_node<TYPE>*>* t_nodes = linked_queue::queue_init<thread_node<TYPE>*>();
    if (!binary_tree::tree_check_empty(b_tree)){
        linked_queue::queue_push(b_nodes, b_tree->root);
        tree->root = r_node_init(b_tree->root);
        tree->cnt = 1;
        linked_queue::queue_push(t_nodes, tree->root);
    }
    while (!linked_queue::queue_check_empty(b_nodes)){
        binary_tree::tree_node<TYPE>* cur_b = linked_queue::queue_pop(b_nodes);
        thread_node<TYPE>* cur_t = linked_queue::queue_pop(t_nodes);
        for (int pos = 0; pos < 2; ++pos) {
            binary_tree::tree_node<TYPE>* child = binary_tree::node_get_child(cur_b, pos);
            if (!binary_tree::node_check_null(child)){
                linked_queue::queue_push(b_nodes, child);
                set_pointer(cur_t, pos, r_node_init(child));
                linked_queue::queue_push(t_nodes, get_pointer(cur_t, pos));
                tree->cnt += 1;
            }
        }
    }
    return tree;
}

// 线索树初始化
T thread_tree<TYPE>* r_tree_init(binary_tree::binary_tree<TYPE>* b_tree){
    thread_tree<TYPE>* tree = r_tree_copy(b_tree);
    thread_node<TYPE>* pre = (thread_node<TYPE>*) nullptr;
    threaded(tree->root, pre);
    return tree;
}
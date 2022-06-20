//
// Created by Lenovo on 2022/5/16.
//

#ifndef C_C___TREE_TRAVERSE_H
#define C_C___TREE_TRAVERSE_H

#endif //C_C___TREE_TRAVERSE_H
#include <main body/c5/binary_tree/binary_tree.h>


// 二叉树的层次遍历
T void tree_level_traverse(binary_tree::binary_tree<TYPE>* tree){
    std::cout << "{";
    linked_queue::linked_queue<binary_tree::tree_node<TYPE>*>* nodes = linked_queue::queue_init<binary_tree::tree_node<TYPE>*>();
    if (!binary_tree::tree_check_empty(tree)){
        linked_queue::queue_push(nodes, tree->root);
    }
    while (!linked_queue::queue_check_empty(nodes)){
        binary_tree::tree_node<TYPE>* cur = linked_queue::queue_pop(nodes);
        binary_tree::node_print(cur);
        std::cout << ", ";
        if (binary_tree::node_has_child(cur, LEFT_CHILD)){
            linked_queue::queue_push(nodes, binary_tree::node_get_child(cur, LEFT_CHILD));
        }
        if (binary_tree::node_has_child(cur, RIGHT_CHILD)){
            linked_queue::queue_push(nodes, binary_tree::node_get_child(cur, RIGHT_CHILD));
        }
    }
    std::cout << "}";
}

// 先序遍历主函数
T void _pre_traverse(binary_tree::tree_node<TYPE>* node){
    if (!binary_tree::node_check_null(node)){
        binary_tree::node_print(node);
        std::cout << ", ";
        _pre_traverse(binary_tree::node_get_child(node, LEFT_CHILD));
        _pre_traverse(binary_tree::node_get_child(node, RIGHT_CHILD));
    }
}

// 二叉树的先序遍历
T void tree_pre_traverse(binary_tree::binary_tree<TYPE>* tree){
    std::cout << "{";
    if (!binary_tree::tree_check_empty(tree)){
        _pre_traverse(tree->root);
    }
    std::cout << "}";
}

// 中序遍历主函数
T void _in_traverse(binary_tree::tree_node<TYPE>* node){
    if (!binary_tree::node_check_null(node)){
        _in_traverse(binary_tree::node_get_child(node, LEFT_CHILD));
        binary_tree::node_print(node);
        std::cout << ", ";
        _in_traverse(binary_tree::node_get_child(node, RIGHT_CHILD));
    }
}

// 二叉树的中序遍历
T void tree_in_traverse(binary_tree::binary_tree<TYPE>* tree){
    std::cout << "{";
    if (!binary_tree::tree_check_empty(tree)){
        _in_traverse(tree->root);
    }
    std::cout << "}";
}

// 后序遍历主函数
T void _post_traverse(binary_tree::tree_node<TYPE>* node){
    if (!binary_tree::node_check_null(node)){
        _post_traverse(binary_tree::node_get_child(node, LEFT_CHILD));
        _post_traverse(binary_tree::node_get_child(node, RIGHT_CHILD));
        binary_tree::node_print(node);
        std::cout << ", ";
    }
}

// 二叉树的后序遍历
T void tree_post_traverse(binary_tree::binary_tree<TYPE>* tree){
    std::cout << "{";
    if (!binary_tree::tree_check_empty(tree)){
        _post_traverse(tree->root);
    }
    std::cout << "}";
}
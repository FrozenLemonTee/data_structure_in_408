//
// Created by Lenovo on 2022/6/21.
//

#ifndef C_C___N_TREE_H
#define C_C___N_TREE_H

#endif //C_C___N_TREE_H
#include <main body/c5/binary_tree/binary_tree.h>

// 多叉树节点定义
T struct n_tree_node{
    TYPE data; // 树节点数据域
    array<n_tree_node<TYPE>*> children; // 树节点孩子列表
    int child_cnt; // 非空子树数量
};

// 多叉树节点初始化
T n_tree_node<TYPE>* node_init(binary_tree::tree_node<TYPE>* b_node, int branches){
    n_tree_node<TYPE>* node = (n_tree_node<TYPE>*)malloc(sizeof(n_tree_node<TYPE>));
    node->data = b_node->data;
    node->children = array<n_tree_node<TYPE>*>(branches);
    node->child_cnt = 0;
    return node;
}

// 设置当前节点的孩子节点
T void node_set_child(n_tree_node<TYPE>* cur, int pos, n_tree_node<TYPE>* child){
    if (pos > cur->child_cnt){
        ILLEGAL_INDEX;
    }
    else if (pos == cur->child_cnt){
        cur->child_cnt += 1;
        cur->children.set(pos, child);
    }
}

// 获取当前节点的孩子节点
T n_tree_node<TYPE>* node_get_child(n_tree_node<TYPE>* cur, int pos){
    if (pos > cur->child_cnt){
        ILLEGAL_INDEX;
    }
    return cur->children.get(pos);
}

// 多叉树定义
T struct n_tree{
    n_tree_node<TYPE>* root; // 根节点
    int branches; // 最大分叉数量
    int cnt; // 节点数量
};

// 多叉树初始化
T n_tree<TYPE>* n_tree_init(binary_tree::binary_tree<TYPE>* b_tree, int branches){
    n_tree<TYPE>* n_tree = (::n_tree<TYPE>*)malloc(sizeof(::n_tree<TYPE>));
    n_tree->branches = branches;
    n_tree->cnt = 0;
    linked_queue::linked_queue<binary_tree::tree_node<TYPE>*>* b_nodes = linked_queue::queue_init<binary_tree::tree_node<TYPE>*>();
    linked_queue::linked_queue<n_tree_node<TYPE>*>* n_nodes = linked_queue::queue_init<n_tree_node<TYPE>*>();
    if (!binary_tree::tree_check_empty(b_tree)){
        n_tree->root = node_init(b_tree->root, n_tree->branches);
        n_tree->cnt += 1;
        linked_queue::queue_push(b_nodes, b_tree->root);
        linked_queue::queue_push(n_nodes, n_tree->root);
    }
    bool pos = LEFT_CHILD;
    binary_tree::tree_node<TYPE>* cur_b;
    while (!linked_queue::queue_check_empty(b_nodes)){
        linked_queue::linked_queue<binary_tree::tree_node<TYPE>*>* tmp = linked_queue::queue_init<binary_tree::tree_node<TYPE>*>();
        int cnt = 0;
        while (cnt < n_tree->branches && !linked_queue::queue_check_empty(b_nodes)){
            if (pos == LEFT_CHILD){
                cur_b = linked_queue::queue_get_front(b_nodes);
            }
            binary_tree::tree_node<TYPE>* child_b = binary_tree::node_get_child(cur_b, pos);
            if (!binary_tree::node_check_null(child_b)){
                cnt += 1;
                linked_queue::queue_push(tmp, child_b);
            }
            if (pos == RIGHT_CHILD){
                linked_queue::queue_pop(b_nodes);
            }
            pos = !pos;
        }
        int i = 0;
        n_tree_node<TYPE>* cur_n = linked_queue::queue_pop(n_nodes);
        while (!linked_queue::queue_check_empty(tmp)){
            linked_queue::queue_push(b_nodes, linked_queue::queue_get_front(tmp));
            node_set_child(cur_n, i, node_init(linked_queue::queue_pop(tmp), n_tree->branches));
            linked_queue::queue_push(n_nodes, node_get_child(cur_n, i));
            i += 1;
        }
    }
    return n_tree;
}
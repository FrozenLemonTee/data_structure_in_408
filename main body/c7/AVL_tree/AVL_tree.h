//
// Created by Lenovo on 2022/10/9.
//

#ifndef C_C___AVL_TREE_H
#define C_C___AVL_TREE_H
#include "global.h"
#define LEFT 0
#define RIGHT 1

// 平衡搜索树节点定义
T struct AVL_node{
    TYPE data; // 数据域
    AVL_node<TYPE>** children; // 指向孩子节点列表的指针
    AVL_node<TYPE>* parent; // 指向父节点的指针
    int height; // 当前树的高度
};

// 返回空节点
T AVL_node<TYPE>* null_node(){
    return (AVL_node<TYPE>*) nullptr;
}

// 判断节点是否为空
T bool is_null_node(AVL_node<TYPE>* node){
    return node == null_node<TYPE>();
}

// 获取节点数据域
T TYPE node_get_val(AVL_node<TYPE>* node){
    if (is_null_node(node)){
        NULL_PTR;
    }
    return node->data;
}

// 设置节点数据域
T void node_set_val(AVL_node<TYPE>* node, TYPE data){
    if (is_null_node(node)){
        NULL_PTR;
    }
    node->data = data;
}

// 获取节点树高
T TYPE node_get_height(AVL_node<TYPE>* node){
    return is_null_node(node) ? 0 : node->height;
}

// 获取节点的孩子节点，0为左孩子，1为右孩子
T AVL_node<TYPE>* node_get_child(AVL_node<TYPE>* node, bool pos){
    if (is_null_node(node)){
        NULL_PTR;
    }
    return node->children[pos];
}

// 获取节点的父节点
T AVL_node<TYPE>* node_get_parent(AVL_node<TYPE>* node){
    if (is_null_node(node)){
        NULL_PTR;
    }
    return node->parent;
}

// 更新节点的树高
T void node_set_height(AVL_node<TYPE>* node){
    if (is_null_node(node)){
        NULL_PTR;
    }
    node->height = 1 + max(node_get_height(node_get_child(node, LEFT)),
                           node_get_height(node_get_child(node, RIGHT)));
}

// 更新节点与孩子的双向连接
T void node_connect(AVL_node<TYPE>* node, bool pos, AVL_node<TYPE>* child){
    if (is_null_node(node)){
        NULL_PTR;
    }
    node->children[pos] = child;
    if (!is_null_node(child)){
        child->parent = node;
    }
}

// 计算平衡因子
T int balance_factor(AVL_node<TYPE>* node){
    return node_get_height(node_get_child(node, LEFT)) - node_get_height(node_get_child(node, RIGHT));
}

// 新节点构造
T AVL_node<TYPE>* node_init(TYPE data){
    AVL_node<TYPE>* node = (AVL_node<TYPE>*) malloc(sizeof(AVL_node<TYPE>));
    node->data = data;
    node->children = (AVL_node<TYPE>**) malloc(sizeof(AVL_node<TYPE>*) * 2);
    node->parent = null_node<TYPE>();
    for (int i = 0; i < 2; ++i) {
        node_connect(node, i, null_node<TYPE>());
    }
    node_set_height(node);
    return node;
}

// 平衡搜索树定义
T struct AVL_tree{
    int cnt; // 搜索树节点数量
    AVL_node<TYPE>* root; // 根节点指针
};

// 平衡搜索树构造
T AVL_tree<TYPE>* tree_init(){
    AVL_tree<TYPE>* tree = (AVL_tree<TYPE>*) malloc(sizeof(AVL_tree<TYPE>));
    tree->cnt = 0;
    tree->root = null_node<TYPE>();
    return tree;
}

// 获取树节点总数
T int tree_get_size(AVL_tree<TYPE>* tree){
    return tree->cnt;
}

// 获取根节点
T AVL_node<TYPE>* tree_get_root(AVL_tree<TYPE>* tree){
    return tree->root;
}

// 判断节点是否是根节点
T bool is_root(AVL_node<TYPE>* node){
    return node == node_get_parent(node);
}

// 设置根节点
T void tree_set_root(AVL_tree<TYPE>* tree, AVL_node<TYPE>* node){
    tree->root = node;
    if (!is_null_node(node)){
        node->parent = node;
    }
}

// 判断树是否为空树
T bool is_tree_empty(AVL_tree<TYPE>* tree){
    return !tree_get_size(tree);
}

// 删除节点
T void node_delete(AVL_tree<TYPE>* tree, AVL_node<TYPE>* node){
    if (is_root(node)){
        free(tree_get_root(tree));
        tree_set_root(tree, null_node<TYPE>());
    } else{
        AVL_node<TYPE>* parent = node_get_parent(node);
        bool pos = node_get_child(parent, RIGHT) == node;
        free(node_get_child(parent, pos));
        node_connect(parent, pos, null_node<TYPE>());
    }
}

// 从任意节点出发查找离待操作位置最近的父节点位置
T AVL_node<TYPE>* find_pos(AVL_node<TYPE>* node, TYPE data){
    AVL_node<TYPE>* pos = node;
    while (!is_null_node(pos) && data != node_get_val(pos)){
        AVL_node<TYPE>* child = node_get_child(pos, data > node_get_val(pos));
        if (is_null_node(child)){
            break;
        }
        pos = child;
    }
    return pos;
}

// 检查树中是否包含被搜索元素
T bool tree_contains(AVL_tree<TYPE>* tree, TYPE data){
    AVL_node<TYPE>* find = find_pos(tree_get_root(tree), data);
    return !is_null_node(find) && data == node_get_val(find);
}

// 查找最大（小元素），pos为0时返回最小值，pos为1时返回最大值，树空时返回NULL
T TYPE tree_limit_val(AVL_tree<TYPE>* tree, bool pos){
    if (!is_tree_empty(tree)){
        AVL_node<TYPE>* cur = tree_get_root(tree);
        while (!is_null_node(node_get_child(cur, pos))){
            cur = node_get_child(cur, pos);
        }
        return node_get_val(cur);
    }
    return (TYPE)NULL;
}

// 返回树中最小元素
T TYPE tree_min_val(AVL_tree<TYPE>* tree){
    return tree_limit_val(tree, 0);
}

// 返回树中最大元素
T TYPE tree_max_val(AVL_tree<TYPE>* tree){
    return tree_limit_val(tree, 1);
}

// 单次旋转调整。direction为0进行右旋，direction为1进行左旋
T void rotate(AVL_tree<TYPE>* tree, AVL_node<TYPE>* node1, bool direction){
    AVL_node<TYPE>* node2 = node_get_child(node1, direction ? RIGHT : LEFT);
    if (!is_root(node1)){
        AVL_node<TYPE>* parent = node_get_parent(node1);
        node_connect(parent, node_get_child(parent, RIGHT) == node1, node2);
    } else{
        tree_set_root(tree, node2);
    }
    node_connect(node1, direction ? RIGHT : LEFT, node_get_child(node2, direction ? LEFT : RIGHT));
    node_connect(node2, direction ? LEFT : RIGHT, node1);
    node_set_height(node1);
    node_set_height(node2);
}

// 树的平衡调整：LL为右旋，RR为左旋，LR为左旋+右旋，RL为右旋+左旋；sub为1时为插入操作后调整，为0时为删除操作后调整
T void adjust(AVL_tree<TYPE>* tree, AVL_node<TYPE>* cur, bool sub){
    if (abs(balance_factor(cur)) < 2){
        return;
    }
    AVL_node<TYPE>* node1 = sub ? node_get_parent(cur) : cur;
    AVL_node<TYPE>* node2 = sub ? cur : node_get_child(cur, balance_factor(cur) < 0);
    if (balance_factor(node1) * balance_factor(node2) > 0){
        rotate(tree, node1, balance_factor(node2) < 0);
    } else{
        bool direction = balance_factor(node2) < 0;
        rotate(tree, node2, direction);
        rotate(tree, node1, !direction);
    }
}

T void adjust_sub(AVL_tree<TYPE>* tree, AVL_node<TYPE>* cur){
    if (abs(balance_factor(cur)) < 2){
        return;
    }
    AVL_node<TYPE>* node1 = cur;
    AVL_node<TYPE>* node2 = node_get_child(cur, balance_factor(cur) < 0);
    if (balance_factor(node1) * balance_factor(node2) > 0){
        rotate(tree, node1, balance_factor(node2) < 0);
    } else{
        bool direction = balance_factor(node2) < 0;
        rotate(tree, node2, direction);
        rotate(tree, node1, !direction);
    }
}

// 插入新元素
// todo: bugs to fix
T bool tree_insert(AVL_tree<TYPE>* tree, TYPE data){
    AVL_node<TYPE>* find = find_pos(tree_get_root(tree), data);
    if (!is_tree_empty(tree)){
        if (data == node_get_val(find)){
            return false;
        }
        AVL_node<TYPE>* cur = node_init(data);
        node_connect(find, data > node_get_val(find), cur);
        tree->cnt += 1;
        // 此处进行调整操作
        while (!is_root(cur)){
            node_set_height(node_get_parent(cur));
            adjust(tree, cur, 0);
            cur = node_get_parent(cur);
        }
        return true;
    }
    tree_set_root(tree, node_init(data));
    node_set_height(tree_get_root(tree));
    tree->cnt += 1;
    return true;
}

// 删除元素
// todo: bugs to fix
T bool tree_pop(AVL_tree<TYPE>* tree, TYPE data){
    AVL_node<TYPE>* find = find_pos(tree_get_root(tree), data);
    if (!is_tree_empty(tree)){
        if (data != node_get_val(find)){
            return false;
        }
        AVL_node<TYPE>* pre = find_pos(node_get_child(find, LEFT), data);
        AVL_node<TYPE>* cur;
        if (!is_null_node(pre)){
            cur = node_get_parent(pre);
            node_set_val(find, node_get_val(pre));
            node_delete(tree, pre);
        } else{
            if(is_null_node(node_get_child(find, RIGHT))){
                cur = node_get_parent(find);
                node_delete(tree, find);
            } else{
                cur = find;
                node_set_val(find, node_get_val(node_get_child(find, RIGHT)));
                node_delete(tree, node_get_child(find, RIGHT));
            }
        }
        tree->cnt -= 1;
        // 此处进行调整操作
        while (!is_tree_empty(tree) && !is_root(cur)){
            node_set_height(cur);
            adjust(tree, cur, 0);
            cur = node_get_parent(cur);
        }
        return true;
    }
    return false;
}

#endif //C_C___AVL_TREE_H

//
// Created by Lenovo on 2022/4/21.
//

#ifndef C_C___NEST_LIST_H
#define C_C___NEST_LIST_H

#endif //C_C___NEST_LIST_H
#include "global.h"


// 嵌套节点定义
T struct node{
    int flag; // 节点标识符：0时为带值节点，为1时为嵌套表哨兵节点
    ::node<TYPE>* type_pointer; // 若该节点为带值节点，则该域为节点数据域；若该节点为哨兵节点，则该域为该嵌套表的表体指针域
    ::node<TYPE>* next; // 该节点的后继节点指针域
    ::node<TYPE>* tail; // 尾结点指针
};

// 初始化一个带值节点
T ::node<TYPE>* node_init(TYPE val){
    ::node<TYPE>* node = (::node<TYPE>*)malloc(sizeof(::node<TYPE>));
    node->flag = 0;
    node->type_pointer = (::node<TYPE>*)(val);
    node->next = NULL;
    node->tail = node;
    return node;
}

// 初始化一个哨兵节点
T node<TYPE>* node_init(){
    ::node<TYPE>* node = (::node<TYPE>*)malloc(sizeof(::node<TYPE>));
    node->flag = 1;
    node->type_pointer = NULL;
    node->next = NULL;
    node->tail = node;
    return node;
}

// 检查欲访问的节点类型是否符合操作
T bool node_type_check(::node<TYPE>* node, int type){
    return node->flag == type;
}

// 返回最外层嵌套表的长度
T int node_length(::node<TYPE>* node){
    ::node<TYPE>* pointer = node->type_pointer;
    int length = 0;
    while (pointer){
        length += 1;
        pointer = pointer->next;
    }
    return length;
}

// 返回整个嵌套表元素的个数
T int node_count(::node<TYPE>* node){
    ::node<TYPE>* pointer = node->type_pointer;
    int cnt = 0;
    while (pointer){
        if (node_type_check(pointer, 1)){
            cnt += node_count(pointer);
        } else{
            cnt += 1;
        }
        pointer = pointer->next;
    }
    return cnt;
}

// 返回整个嵌套表的最大嵌套层数
T int node_depth(::node<TYPE>* node){
    ::node<TYPE>* pointer = node->type_pointer;
    int depth = 0;
    while (pointer){
        if (node_type_check(pointer, 1)){
            int cur_depth = node_depth(pointer) + 1;
            depth = max(cur_depth, depth);
        }
        pointer = pointer->next;
    }
    return depth;
}

// 在当前层最后插入新节点
T void node_add_end(::node<TYPE>* node, ::node<TYPE>* next){
    if (node->tail == node){
        node->type_pointer = next;
    } else{
        node->tail->next = next;
    }
    node->tail = next;
}

// 在当前层删除最后一个节点并返回
T ::node<TYPE>* node_delete_end(::node<TYPE>* node){
    if (node_type_check(node, 0)){
        TYPE_ERROR;
    }
    ::node<TYPE>* pointer = node->type_pointer;
    while (pointer){
        if (pointer->next == node->tail){
            node->tail = node;
            ::node<TYPE>* res = node->next;
            node->next = NULL;
            return res;
        }
        if (pointer->next->next == node->tail){
            ::node<TYPE>* res = node->tail;
            pointer->next->next = NULL;
            node->tail = pointer->next;
            return res;
        }
        pointer = pointer->next;
    }
    return NULL;
}

// 打印单个节点
T void node_print(::node<TYPE>* node){
    if (node_type_check(node, 1)){
        std::cout << "(LIST#" << node << ", x" << node_length(node) << ", #" << node->next << ")";
    } else{
        std::cout << "(NODE#" << node << ", " << (TYPE)node->type_pointer << ", #" << node->next << ")";
    }
}

// 打印嵌套表
T void node_list_print(::node<TYPE>* node){
    if (node == NULL){
        std::cout << "NULL" << std::endl;
        return;
    }
    if (node_type_check(node, 1)){
        node_print(node);
        std::cout << ": [";
        ::node<TYPE>* pointer = node->type_pointer;
        while (pointer){
            node_print(pointer);
            std::cout << "->";
            pointer = pointer->next;
        }
    }
    std::cout << "]" << std::endl;
}
//
// Created by Lenovo on 2022/6/3.
//

#ifndef C_C___ADJACENCY_GRAPH_H
#define C_C___ADJACENCY_GRAPH_H

#endif //C_C___ADJACENCY_GRAPH_H
#include "global.h"

#define DIRECTED_GRAPH 1
#define UNDIRECTED_GRAPH 0


// 邻接矩阵图定义
T struct adjacency_graph{
    bool directed; // 图的类型，0为无向图，1为有向图
    int nodes_cnt; // 节点数量
    TYPE* nodes; // 节点列表
    int sides_cnt; // 边的数量
    int** sides; // 边的邻接矩阵
};

// 邻接矩阵图初始化
T adjacency_graph<TYPE>* graph_init(bool type, array<TYPE>* nodes){
    adjacency_graph<TYPE>* graph = (adjacency_graph<TYPE>*)malloc(sizeof(adjacency_graph<TYPE>));
    graph->directed = type;
    graph->nodes_cnt = nodes->size();
    graph->sides_cnt = 0;
    graph->nodes = (TYPE*)malloc(sizeof(TYPE) * graph->nodes_cnt);
    for (int i = 0; i < nodes->size(); ++i) {
        graph->nodes[i] = nodes->get(i);
    }
    int init = type ? INT_MAX : 0;
    graph->sides = (int**)malloc(sizeof(int*) * graph->nodes_cnt);
    for (int i = 0; i < graph->nodes_cnt; ++i) {
        graph->sides[i] = (int*)malloc(sizeof(int) * graph->nodes_cnt);
        for (int j = 0; j < graph->nodes_cnt; ++j) {
            graph->sides[i][j] = init;
        }
    }
    return graph;
}

// 检查边的设置是否合法
T bool graph_side_check(adjacency_graph<TYPE>* graph, int node1, int node2, int weight){
    if (node1 == node2 || node1 >= graph->nodes_cnt || node2 >= graph->nodes_cnt){
        return false;
    }
    return graph->directed || (weight == 0 || weight == 1);
}

// 获取图的类型
T bool graph_get_type(adjacency_graph<TYPE>* graph){
    return graph->directed;
}

// 设置边的权值
T void graph_set_side(adjacency_graph<TYPE>* graph, int node1, int node2, int weight){
    if (graph_side_check(graph, node1, node2, weight)){
        GRAPH_SIDE_ERROR;
    }
    graph->sides[node1][node2] = weight;
    if (graph_get_type(graph) == UNDIRECTED_GRAPH){
        graph->sides[node2][node1] = weight;
    }
    int init = graph_get_type(graph) ? INT_MAX : 0;
    if (graph->sides[node1][node2] == init && weight != init){
        graph->sides_cnt += 1;
    } else if (graph->sides[node1][node2] != init && weight == init){
        graph->sides_cnt -= 1;
    }
}

// 获取某节点的度
T array<int> graph_get_degree(adjacency_graph<TYPE>* graph, int node){
    if (node >= graph->nodes_cnt){
        ILLEGAL_INDEX;
    }
    array<int> res = array<int>(2);
    res.set(0, 0);
    res.set(1, 0);
    int init = graph_get_type(graph) ? INT_MAX : 0;
    for (int i = 0; i < graph->nodes_cnt; ++i) {
        if (graph->sides[node][i] != init){
            res.set(0, res.get(0) + 1);
        }
    }
    if (graph_get_type(graph) == DIRECTED_GRAPH){
        for (int i = 0; i < graph->nodes_cnt; ++i) {
            if (graph->sides[i][node] != init){
                res.set(1, res.get(1) + 1);
            }
        }
    } else{
        res.set(1, res.get(0));
    }
    return res;
}

// 打印图
T void graph_print(adjacency_graph<TYPE>* graph){
    int init = graph_get_type(graph) ? INT_MAX : 0;
    for (int i = 0; i < graph->nodes_cnt; ++i) {
        std::cout << "(" << graph->nodes[i] << ", " << "#" << i << "): ";
        for (int j = 0; j < graph->nodes_cnt; ++j) {
            if (graph->sides[i][j] != init){
                std::cout << graph->sides[i][j] << "(#" << j << "), ";
            }
        }
        std::cout << std::endl;
    }
}
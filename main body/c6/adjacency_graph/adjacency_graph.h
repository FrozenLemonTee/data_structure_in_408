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
T adjacency_graph<TYPE>* graph_init(bool type, array<TYPE> nodes){
    adjacency_graph<TYPE>* graph = (adjacency_graph<TYPE>*)malloc(sizeof(adjacency_graph<TYPE>));
    graph->directed = type;
    graph->nodes_cnt = nodes.size();
    graph->sides_cnt = 0;
    graph->nodes = (TYPE*)malloc(sizeof(TYPE) * graph->nodes_cnt);
    for (int i = 0; i < nodes.size(); ++i) {
        graph->nodes[i] = nodes.get(i);
    }
    graph->sides = (int**)malloc(sizeof(int*) * graph->nodes_cnt);
    for (int i = 0; i < graph->nodes_cnt; ++i) {
        graph->sides[i] = (int*)malloc(sizeof(int) * graph->nodes_cnt);
        for (int j = 0; j < graph->nodes_cnt; ++j) {
            graph->sides[i][j] = INT_MAX;
        }
    }
    return graph;
}

// 检查边的设置是否合法
T bool graph_side_check(adjacency_graph<TYPE>* graph, int node1, int node2){
    if (node1 == node2 || node1 >= graph->nodes_cnt || node2 >= graph->nodes_cnt){
        return false;
    }
    return true;
}

// 获取图的类型
T bool graph_get_type(adjacency_graph<TYPE>* graph){
    return graph->directed;
}

// 设置边的权值
T void graph_set_side(adjacency_graph<TYPE>* graph, int node1, int node2, int weight){
    if (!graph_side_check(graph, node1, node2)){
        GRAPH_SIDE_ERROR;
    }
    if (graph->sides[node1][node2] == INT_MAX && weight != INT_MAX){
        graph->sides_cnt += 1;
    } else if (graph->sides[node1][node2] != INT_MAX && weight == INT_MAX){
        graph->sides_cnt -= 1;
    }
    graph->sides[node1][node2] = weight;
    if (graph_get_type(graph) == UNDIRECTED_GRAPH){
        graph->sides[node2][node1] = weight;
    }
}

// 获取某节点的出度与入度
T array<int> graph_get_degree(adjacency_graph<TYPE>* graph, int node){
    if (node >= graph->nodes_cnt){
        ILLEGAL_INDEX;
    }
    array<int> res = array<int>({0, 0});
    for (int i = 0; i < graph->nodes_cnt; ++i) {
        if (graph->sides[node][i] != INT_MAX){
            res.set(0, res.get(0) + 1);
        }
    }
    if (graph_get_type(graph) == DIRECTED_GRAPH){
        for (int i = 0; i < graph->nodes_cnt; ++i) {
            if (graph->sides[i][node] != INT_MAX){
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
    const char* type = graph_get_type(graph) ? "DIRECTED" : "UNDIRECTED";
    std::cout << "(" << type << " adjacency_graph #" << graph << ", node: " << graph->nodes_cnt
              << ", sides: " << graph->sides_cnt << ")" << std::endl;
    for (int i = 0; i < graph->nodes_cnt; ++i) {
        std::cout << "(" << graph->nodes[i] << ", " << "#" << i << "): ";
        for (int j = 0; j < graph->nodes_cnt; ++j) {
            if (graph->sides[i][j] != INT_MAX){
                std::cout << graph->sides[i][j] << "(#" << j << "), ";
            }
        }
        std::cout << std::endl;
    }
}
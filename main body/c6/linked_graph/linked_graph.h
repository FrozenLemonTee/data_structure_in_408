//
// Created by Lenovo on 2022/6/6.
//

#ifndef C_C___LINKED_GRAPH_H
#define C_C___LINKED_GRAPH_H

#endif //C_C___LINKED_GRAPH_H
#include <main body/c2/linked_list/linked_list.h>


#define DIRECTED_GRAPH 1
#define UNDIRECTED_GRAPH 0

// 邻接表图定义
T struct linked_graph{
    bool directed; // 图的类型，0为无向图，1为有向图
    int nodes_cnt; // 节点数量
    TYPE* nodes; // 节点列表
    int sides_cnt; // 边的数量
    linked_list<array<int>>** sides; // 边的邻接表，对于每条链表内的每个元素：首项存储邻接点存储索引，次项存储边的权值
};

// 邻接表图初始化
T linked_graph<TYPE>* graph_init(bool type, array<TYPE> nodes){
    linked_graph<TYPE>* graph = (linked_graph<TYPE>*)malloc(sizeof(linked_graph<TYPE>));
    graph->directed = type;
    graph->nodes_cnt = nodes.size();
    graph->sides_cnt = 0;
    graph->nodes = (TYPE*)malloc(sizeof(TYPE) * graph->nodes_cnt);
    for (int i = 0; i < nodes.size(); ++i) {
        graph->nodes[i] = nodes.get(i);
    }
    graph->sides = (linked_list<array<int>>**)malloc(sizeof(linked_list<array<int>>*) * graph->nodes_cnt);
    for (int i = 0; i < graph->nodes_cnt; ++i) {
        graph->sides[i] = list_init<array<int>>();
    }
    return graph;
}

// 检查边的设置是否合法
T bool graph_side_check(linked_graph<TYPE>* graph, int node1, int node2, int weight){
    if (node1 == node2 || node1 >= graph->nodes_cnt || node2 >= graph->nodes_cnt || weight == INT_MAX){
        return false;
    }
    return true;
}

// 获取图的类型
T bool graph_get_type(linked_graph<TYPE>* graph){
    return graph->directed;
}

// 查找图中的某条边，存在返回在邻接表中的索引，不存在则返回-1
T int graph_find_side(linked_graph<TYPE>* graph, int node1, int node2){
    linked_list<array<int>>* list = graph->sides[node1];
    if (!list_check_empty(list)){
        int node = list_find_by_index(list, 0).get(0);
        for (int i = 0; i < list_length(list); ++i) {
            if (node == node2){
                return i;
            }
        }
    }
    return -1;
}

// 设置边的权值
T void graph_set_side(linked_graph<TYPE>* graph, int node1, int node2, int weight){
    if (!graph_side_check(graph, node1, node2, weight)){
        GRAPH_SIDE_ERROR;
    }
    int pos = graph_find_side(graph, node1, node2);
    if (pos == -1){
        graph->sides_cnt += 1;
        list_insert(graph->sides[node1], array<int>({node2, weight}));
        if (graph_get_type(graph) == UNDIRECTED_GRAPH){
            list_insert(graph->sides[node2], array<int>({node1, weight}));
        }
    } else{
        array<int> arr1 = list_find_by_index(graph->sides[node1], pos);
        arr1.set(1, weight);
        if (graph_get_type(graph) == UNDIRECTED_GRAPH) {
            array<int> arr2 = list_find_by_index(graph->sides[node2], graph_find_side(graph, node2, node1));
            arr2.set(1, weight);
        }
    }
}

// 删除图中的某条边，并返回边的权值，若边已删除则返回INT_MAX
T int graph_delete_side(linked_graph<TYPE>* graph, int node1, int node2){
    if (!graph_side_check(graph, node1, node2, 0)){
        GRAPH_SIDE_ERROR;
    }
    int pos = graph_find_side(graph, node1, node2);
    if (pos != -1){
        graph->sides_cnt -= 1;
        int res = list_pop(graph->sides[node1], pos).get(1);
        if (graph_get_type(graph) == UNDIRECTED_GRAPH){
            list_pop(graph->sides[node2], graph_find_side(graph, node2, node1));
        }
        return res;
    }
    return INT_MAX;
}

// 获取某节点的出度与入度
T array<int> graph_get_degree(linked_graph<TYPE>* graph, int node){
    if (node >= graph->nodes_cnt){
        ILLEGAL_INDEX;
    }
    array<int> res = array<int>({list_length(graph->sides[node]), 0});
    if (graph_get_type(graph) == UNDIRECTED_GRAPH){
        res.set(1, res.get(0));
    } else{
        for (int i = 0; i < graph->nodes_cnt; ++i) {
            if (graph_find_side(graph, i, node) != -1){
                res.set(1, res.get(1) + 1);
            }
        }
    }
    return res;
}

// 打印图
T void graph_print(linked_graph<TYPE>* graph){
    const char* type = graph_get_type(graph) ? "DIRECTED" : "UNDIRECTED";
    std::cout << "(" << type << " linked_graph #" << graph << ", node: " << graph->nodes_cnt
              << ", sides: " << graph->sides_cnt << ")" << std::endl;
    for (int i = 0; i < graph->nodes_cnt; ++i) {
        std::cout << "(" << graph->nodes[i] << ", " << "#" << i << "): ";
        if (list_length(graph->sides[i])){
            list_node<array<int>>* pointer = list_find_by_index_(graph->sides[i], 0);
            for (int j = 0; j < list_length(graph->sides[i]); ++j) {
                array<int> cur = pointer->data;
                std::cout << cur.get(1) << "(#" << cur.get(0) << "), ";
                pointer = pointer->next_node;
            }
        }
        std::cout << std::endl;
    }
}
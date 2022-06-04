//
// Created by Lenovo on 2022/6/3.
//
#include "adjacency_graph.h"

array<int> nodes_create(int num){
    array<int> nodes = array<int>(num);
    for (int i = 0; i < num; ++i) {
        nodes.set(i, rand_range(0, num));
    }
    return nodes;
}

// flag为1，输出提示信息；flag为0，不输出提示信息
void test_set_side(adjacency_graph<int>* graph, int flag, int num){
    for (int i = 0; i < num; ++i) {
        int node1 = rand_range(0, graph->nodes_cnt);
        int node2 = rand_range(0, graph->nodes_cnt);
        while (node2 == node1){
            node2 = rand_range(0, graph->nodes_cnt);
        }
        int weight = rand_range(0, graph->nodes_cnt);
        if (flag){
            std::cout << node1 << "---" << node2 << ": " << weight << std::endl;
        }
        graph_set_side(graph, node1, node2, weight);
    }
}

void test_get_degree(adjacency_graph<int>* graph, int num){
    if (num){
        graph_print(graph);
        for (int i = 0; i < num; ++i) {
            int node = rand_range(0, graph->nodes_cnt);
            array<int> degree = graph_get_degree(graph, node);
            std::cout << "node #" << node << " 's out-degree: " << degree.get(0) << std::endl;
            std::cout << "node #" << node << " 's in-degree: " << degree.get(1) << std::endl;
        }
    }
}

int main(){
    adjacency_graph<int>* graph1 = graph_init<int>(UNDIRECTED_GRAPH, nodes_create(20));
    test_set_side(graph1, 1, 20);
    print_separate();
    test_get_degree(graph1, 20);
    print_separate();
    adjacency_graph<int>* graph2 = graph_init<int>(DIRECTED_GRAPH, nodes_create(20));
    test_set_side(graph2, 1, 20);
    print_separate();
    test_get_degree(graph2, 20);
    return 0;
}
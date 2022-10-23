//
// Created by Lenovo on 2022/10/9.
//

#include "main body/c3/linked_queue/linked_queue.h"
#include "AVL_tree.h"

T void tree_level_traverse(AVL_tree<TYPE>* tree){
    std::cout << "{";
    linked_queue::linked_queue<::AVL_node<TYPE>*>* nodes = linked_queue::queue_init<::AVL_node<TYPE>*>();
    if (!::is_tree_empty(tree)){
        linked_queue::queue_push(nodes, tree->root);
    }
    while (!linked_queue::queue_check_empty(nodes)){
        ::AVL_node<TYPE>* cur = linked_queue::queue_pop(nodes);
        std::cout << "(#" << cur << ", val: " << node_get_val(cur) << ", "
        << "L: #" << node_get_child(cur, LEFT) << ", "
        << "R: #" << node_get_child(cur, RIGHT) << ", "
        << "P: #" << node_get_parent(cur) << ")";
        std::cout << ", ";
        for (int i = 0; i < 2; ++i) {
            if (!is_null_node(node_get_child(cur, i))){
                linked_queue::queue_push(nodes, node_get_child(cur, i));
            }
        }
    }
    std::cout << "}" << std::endl;
}

int main(){
    AVL_tree<int>* tree = tree_init<int>();
    for (int i = 1; i < 21; ++i) {
        tree_insert(tree, i);
        tree_level_traverse(tree);
    }
    while (!is_tree_empty(tree)){
        int val = rand_range(1, 20);
        while (!tree_contains(tree, val)){
            val = rand_range(1, 20);
        }
        std::cout << "delete: " << val << std::endl;
        tree_pop(tree, val);
    }
    for (int i = 1; i < 21; ++i) {
        tree_insert(tree, i);
    }
    print_separate();
    bool pos = 0;
    while (!is_tree_empty(tree)){
        int val = pos ? tree_max_val(tree) : tree_min_val(tree);
        std::cout << "delete: " << val << std::endl;
        tree_pop(tree, val);
        pos = !pos;
    }
    return 0;
}
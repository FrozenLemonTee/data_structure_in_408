#include "main body/c5/tree_traverse/tree_traverse.h"

void delete_node(binary_tree::tree_node<int>* node, int val){
    if (!binary_tree::node_check_null(node)){
        for (int pos = 0; pos < 2; ++pos) {
            binary_tree::tree_node<int>* child = binary_tree::node_get_child(node, pos);
            if (!binary_tree::node_check_null(child) && child->data == val){
                binary_tree::node_set_child(node, pos, (binary_tree::tree_node<int>*) nullptr);
            } else{
                delete_node(child, val);
            }
        }
    }
}

void tree_delete_node_by_val(binary_tree::binary_tree<int>* tree, int val){
    if (!binary_tree::tree_check_empty(tree)){
        if (tree->root->data == val){
            tree->root = (binary_tree::tree_node<int>*) nullptr;
        } else{
            delete_node(tree->root, val);
        }
    }
}

int main(){
    binary_tree::binary_tree<int>* tree =
            binary_tree::tree_init(array<int>({2, 9, 8, 9, 7, 4, 6, 3, 2, 8, 5, 1, 7, 9, 1}));
    std::cout << "before:" << std::endl;
    tree_level_traverse(tree);
    std::cout << std::endl;
    tree_delete_node_by_val(tree, 9);
    std::cout << "after:" << std::endl;
    tree_level_traverse(tree);
    return 0;
}
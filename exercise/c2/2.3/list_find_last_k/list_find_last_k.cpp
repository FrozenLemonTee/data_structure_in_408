//
// Created by Lenovo on 2022/10/23.
//

#include "main body/c2/linked_list/linked_list.h"

// 2023 2.3 22.[2009]
// 1) 算法的基本设计思想:首先判断链表是否为空，若为空则直接返回0，若不为空，则采用双指针pre和pro进行遍历。
//    初始化时pre和pro都指向链头节点，一开始先尝试将pre向链尾方向移动k-1个节点的距离，如果pre没有移动完k-1个节点的距离
//    就已经指向链尾节点，则返回0.若pre还没有指向链尾节点，则同时移动pre与pro指针，直到pre指针指向链尾节点。
//    这时pro所指向的节点便是链表倒数第k个位置的节点，打印该节点data的值，并返回1.
// 2) 算法实现如下。
// 3) 由于pre指针按顺序遍历链表，因此时间复杂度为o(n)。由于算法占用额外空间与链表长度n无关，因此总的空间复杂度为o(1)。

bool list_find_last_k(list_node<int>* head, int k){
    if (head){
        list_node<int>* pre = head;
        for (int i = 0; i < k - 1; ++i) {
            if (pre->next_node){
                pre = pre->next_node;
            } else{
                return false;
            }
        }
        list_node<int>* pro = head;
        while (pre->next_node){
            pre = pre->next_node;
            pro = pro->next_node;
        }
        std::cout << pro->data << std::endl;
        return true;
    }
    return false;
}

list_node<int>* create(int len){
    list_node<int>* head = node_init(INT_MAX);
    list_node<int>* pointer = head;
    for (int i = 0; i < len; ++i) {
        pointer->next_node = node_init(rand_range(0, len));
        pointer = pointer->next_node;
    }
    return head;
}

void test(list_node<int>* head, int k){
    std::cout << "cur list: ";
    list_node<int>* pointer = head;
    while (pointer->next_node){
        pointer = pointer->next_node;
        std::cout << "(#" << pointer << ", " << pointer->data << ", #" << pointer->next_node << "), ";
    }
    std::cout << std::endl;
    bool find = list_find_last_k(head->next_node, k);
    std::cout << "find last " << k << ":" << (find ? "true" : "false") << std::endl;
}

int main(){
    test(create(12), 4);
    print_separate();
    test(create(0), 3);
    print_separate();
    test(create(7), 8);
    print_separate();
    test(create(6), 6);
    return 0;
}
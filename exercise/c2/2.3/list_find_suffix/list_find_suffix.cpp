//
// Created by Lenovo on 2022/10/23.
//

#include "main body/c2/linked_list/linked_list.h"

// 2023 2.3 23.[2012]
// 1) 算法的基本设计思想:分别设置两个指针p1和p2，开始时分别指向str1和str2的链头节点，同时向各自链尾的方向移动。
//    当任意一个指针指向了自己所在链表尾部的指针时（不妨假设是p1），只移动剩下的指针（假设是p2），
//    此时初始化一个变量dis为0记录距离，p2每向链尾方向移动一个节点距离，dis加一，直至p2也指向链尾节点为止。
//    然后使得p1和p2重新指向各自链头的节点。先让p2先移动dis的距离，随后p1与p2指向链尾指针前同步移动，
//    期间若p1与p2节点指向了同一节点则返回指向的节点指针，若已经移动到了链尾，则再判断是否指向了相同的节点，
//    相同则返回指针，不同则返回空指针。
// 2) 算法实现如下。
// 3) 设两链表公共后缀长为c，str1前面的部分长为a，str2前面的部分长为b。第一遍时遍历长度为max(a+c,b+c)，
//    第二遍遍历长度为max(a,b)，因此时间复杂度为o(max(a+c,b+c) + max(a,b))。
//    由于算法占用额外空间与a,b,c无关，因此总的空间复杂度为o(1)。

list_node<char>* list_find_suffix(list_node<char>* head1, list_node<char>* head2){
    list_node<char>* p1 = head1;
    list_node<char>* p2 = head2;
    while (p1->next_node && p2->next_node){
        p1 = p1->next_node;
        p2 = p2->next_node;
    }
    int dis = 0;
    bool pos = p2->next_node;
    while (p1->next_node || p2->next_node){
        if (pos){
            p2 = p2->next_node;
        } else{
            p1 = p1->next_node;
        }
        dis += 1;
    }
    p1 = head1;
    p2 = head2;
    for (int i = 0; i < dis; ++i) {
        if (pos){
            p2 = p2->next_node;
        } else{
            p1 = p1->next_node;
        }
    }
    while (p1->next_node && p2->next_node){
        if (p1 == p2){
            return p1;
        }
        p1 = p1->next_node;
        p2 = p2->next_node;
    }
    return p1 == p2 ? p1 : nullptr;
}

array<list_node<char>*> create(array<int> prefix, int suffix){
    array<list_node<char>*> res = array<list_node<char>*>(2);
    array<list_node<char>*> p = array<list_node<char>*>(2);
    for (int i = 0; i < res.size(); ++i) {
        res.set(i, node_init<char>('z'));
        p.set(i, res.get(i));
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < prefix.get(i); ++j) {
            p.get(i)->next_node = node_init(rand_alpha());
            p.set(i, p.get(i)->next_node);
        }
    }
    for (int i = 0; i < suffix; ++i) {
        list_node<char>* cur = node_init(rand_alpha());
        for (int j = 0; j < 2; ++j) {
            p.get(j)->next_node = cur;
            p.set(j, cur);
        }
    }
    return res;
}

void test(array<int> prefix, int suffix){
    array<list_node<char>*> heads = create(prefix, suffix);
    for (int i = 0; i < 2; ++i) {
        std::cout << "str" << i + 1;
        list_node<char>* p = heads.get(i)->next_node;
        while (p){
            std::cout << "->";
            node_print(p);
            p = p->next_node;
        }
        std::cout << std::endl;
    }
    std::cout << "find suffix: " ;
    list_node<char>* find = list_find_suffix(heads.get(0), heads.get(1));
    if (find){
        node_print(find);
    } else{
        std::cout << "NULL";
    }
    std::cout << std::endl;
}

int main(){
    test(array<int>({3, 5}), 4);
    print_separate();
    test(array<int>({8, 2}), 4);
    print_separate();
    test(array<int>({0, 2}), 4);
    print_separate();
    test(array<int>({6, 0}), 7);
    print_separate();
    test(array<int>({0, 0}), 5);
    print_separate();
    test(array<int>({1, 3}), 0);
    return 0;
}
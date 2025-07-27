#ifndef TREE_H2
#define TREE_H2

#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

struct Node {
    Node* left;
    Node* right;
    int key;
    int info1;
    int info2;
    string str;
    Node(int _key, int _info1, int _info2, string _str);
    ~Node();
};

struct Tree {
    
    Node* root;
    Tree(): root(nullptr) {}
    Node* find_el(Node* node);
    void append(Node* node);
    int del_node(int key);
    void del_leaf(Node* s, Node* p);
    void del_one_child(Node* s, Node* p);
    void show_tree(Node* node);
    Node* find_min(Node* node);

};


#endif



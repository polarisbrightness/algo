#ifndef TREE_H
#define TREE_H

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
    Node(): left(nullptr), right(nullptr), key(0), info1(0), info2(0), str("") {}
};

struct Tree {
    Node* root;

    Tree(): root(nullptr) {}

    Node* find_el(Node* node, int key, int num);
    Node* find_parent(Node* obh, Node* node);
    void del_el(Node* node, int key, int num);
    void append(Node* node);
    void free_node(Node* node);
    void show_tree(Node* tree);
    Node* find_min(Node* node);

    void write_dot_file(Node* node, const std::string& filename);
    void write_dot(Node* node, std::ofstream& out);
    
};


#endif

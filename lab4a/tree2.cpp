#include <iostream>
#include <string.h>
#include <cmath>
#include "tree2.h"
using std::cout;
using std::endl;

Node::Node(int _key, int _info1, int _info2, string _str) : key(_key), info1(_info1), 
info2(_info2), str(_str), left(nullptr), right(nullptr) {}

Node* Tree::find_min(Node* node){
    if(node->left){find_min(node->left);}
    else{return node;}
}
Node::~Node(){
    if(left != nullptr)
        delete left;
    if(right != nullptr)
        delete right;
}


void Tree::append(Node* node){
    if(root == nullptr){
        root = node;
        return;
    }
    


}

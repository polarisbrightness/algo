#include <iostream>
#include <cmath>
#include "tree.h"
#include <fstream>

using std::cout;
using std::endl;

Node::Node(int _key, int _info1, int _info2, string _str) : key(_key), info1(_info1), 
info2(_info2), str(_str), left(nullptr), right(nullptr) {}

Node* Tree::find_min(Node* node){
    if(node->left){return find_min(node->left);}
    else{return node;}
    return nullptr;
}

Node* Tree::find_el(Node* node, int key, int num){
    Node* obh;
    int pr_num = 1;
    obh = node;
    if (obh->key > key){
        if(obh->left){return find_el(obh->left, key, num);}
        else{cout << "element not found" << endl;
        return nullptr;}
    }
    else if (obh->key < key){
        if(obh->right){return find_el(obh->right, key, num);}
        else{cout << "element not found" << endl;
        return nullptr;}
    } 
    else{
        if (pr_num == num){return obh;}
        else {
           return find_el(obh->left, key, num - 1);
        }
    }
    if(obh->left == nullptr && obh->right == nullptr){
        cout << "element not found" << endl;
    }
    return nullptr;
}

Node* Tree::find_parent(Node* obh, Node* node){
    if (obh->key > node->key){
        if(obh->left == node){return obh;}
        else if (obh->left){return find_parent(obh->left, node);}
        else{cout << "element not found" << endl;
        return nullptr;}
    }
    else if (obh->key < node->key){
        if (obh->right == node) {return obh;}
        else if(obh->right){return find_parent(obh->right, node);}
        else{cout << "element not found" << endl;
        return nullptr;}
    } 
    else{
        if (obh->right == node or obh->left == node){return obh;}
        else {
           return find_parent(obh->left, node);
        }
    }
    return nullptr;
}

void Tree::del_el(Node* node, int key, int num){
    Node* obh = find_el(root, key, num);
    if(obh == root){
        if(obh->left == obh->right){
            root = obh->left;
        }
        else{
            Node* min = find_min(obh->right);
            Node* par_min = find_parent(root, min);
            if (min == find_el(root, min->key, 1)){
                if(min->key < par_min->key){par_min -> left = min->right;}
                else{
                    par_min->right = min->right;
                    par_min->left = nullptr;
                }
                min->left = obh->left;
                min->right = obh->right;
                cout << "rooot = "<< root->key <<endl;
            }
            else{
                root = find_el(root, min->key, 1);
                min->left = obh->left;
            }
            obh->left = nullptr;
            obh->right = nullptr;
        }
        return;
    }
    Node* par = find_parent(root, obh);
    cout << "par = " << obh->right->key << endl;
    if(!obh){
        cout << "There is no such element here";
        return;
    }
    if (obh->left == nullptr && obh->right == nullptr){
        if(par->right == obh){par->right = nullptr;}
        if(par->left == obh){par->left = nullptr;}
    }
    else if (obh->left != nullptr && obh->right != nullptr){
        int num = 1; bool q = true; int n = 0;
        while(q){
            cout << "num = " << num << endl;
            if(find_el(root, obh->key, num)->left != nullptr && find_el(root, obh->key, num)->left->key == obh->key ){num++;}
            else{q = false;}
        }
        if (num > 1){
            if(obh->key > par->key){
                par->right = obh->right;}
            else{
                par->left = obh->right;
            }
            obh->left = nullptr;
            obh->right = nullptr;
        }
        else{
            Node* min = find_min(obh->right);
            cout << "min = " << min->key << endl;
            if(obh->key > par->key){
                par->right = find_el(root, min->key, 1);}
            else{
                par->left = find_el(root, min->key, 1);
            }
            min->left = obh->left;
            obh->left = nullptr;
            obh->right = nullptr;
        }
    }

    else {
        if (obh->key < par->key){
            if (obh->right != nullptr){par->left = obh->right;}
            else{par->left = obh->left;}
            return;}
        else{
            if (obh->right != nullptr){par->right = obh->right;}
            else{par->right = obh->left;}
            return;
        }
    }

}

void Tree::free_node(Node* node){
    if(node->left != nullptr)
        node->left = nullptr;
    if(node->right != nullptr)
        node->right = nullptr;
    cout << node->key << " element was deleted" << endl;
}

void Tree::show_tree(Node* obh){
    if (!obh) return;
    if (obh->left == obh->right){
        if (obh != root && obh->left == nullptr){
            int i = 0; int key;
            Node* par = find_parent(root, obh);
            key = par->key;
            while(obh->key == key){
                cout << " " << par->key << endl;
                if (par != root){
                    par = find_parent(root, par);
                    key = par->key;
                }
                else {key = -1;}
            }}
        if (obh->left == nullptr){
            if(obh->key) cout << " "<< obh->key<< endl;}
        else{show_tree(obh->left);}
    }
    else{
        show_tree(obh->left);
        if (obh != root){
            Node* par = find_parent(root, obh); int key;
            key = par->key;
            while(obh->key == key){
                cout << " " << par->key << endl;
                if (par != root){
                    par = find_parent(root, par);
                    key = par->key;
                }
                else {key = -1;}
            }}
        if(obh->key) cout << " "<< obh->key<< endl;
        show_tree(obh->right);
    }
    return;
}

void Tree::append(Node* node){
    int y = 0;
    Node* obh;
    obh = root;
    if(root == nullptr){
        root = node;
        return;
    }
    else{
        while(y == 0){
            if (obh->key < node->key){
                if (obh->right != nullptr){
                    obh = obh->right;
                }
                else{
                    obh->right = node;
                    cout << "element was inserted" << endl;
                    return;
                }
            }
            else if (obh->key > node->key){
                if (obh->left != nullptr){
                    obh = obh->left;
                }
                else {
                    obh->left = node;
                    cout << "element was inserted" << endl;
                    return;
                }
            }
            else {
                while (obh->left != nullptr && obh->key == node->key && obh->left->key == node->key){
                    obh = obh->left;
                }
                node->left = obh->left;
                node->right = obh->right;
                obh->left = node;
                obh->right = node;
                cout << "element was inserted" << endl;
                return;
            }
        }
    }
}

void Tree::write_dot_file(Node* obh, const std::string& filename ) {
    std::ofstream out;
    out.open(filename);
    out << "digraph G {\n";
    write_dot(root, out);
    out << "}\n";
    out.close();
}

void Tree::write_dot(Node* obh, std::ofstream& out) {
    if (!obh) return;
    if (obh->left == obh->right){
        if (obh->left == nullptr){return;}
        out << " " << obh->key << " -> " << obh->left->key << endl;
        write_dot(obh->left, out);
    }
    else{
        if(obh->left != nullptr) write_dot(obh->left, out);
        if(obh->left != nullptr) out << " " << obh->key << " -> " << obh->left->key << endl;
        if(obh->right != nullptr) out << " " << obh->key << " -> " << obh->right->key << endl;
        if(obh->right != nullptr) write_dot(obh->right, out);
    }
    return;
}

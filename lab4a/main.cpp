#include <iostream>
#include <iterator>
#include <cmath>
#include "tree.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

int main(){

    Tree tree;

    vector<Node> nodes;

    string line;
    std::ifstream in("tree_nodes.txt");
    if (in.is_open())
    {
        int key;
        int info1;
        int info2;
        string str;
        while (in >> key)
        {
            in >> info1 >> info2 >> str;
            nodes.push_back(Node{key, info1, info2, str});
        }
        in.close();
    }
    for(auto it = nodes.begin(); it < nodes.end(); ++it){
        tree.append(&(*it));
        cout << &(*it) << endl;
    }


    //cout << "key = " << tree.find_el(tree.root, 7, 1)<< endl;
    // //cout << "key = " << tree.find_parent(tree.root, &node7)->key << endl;
    // cout << "key = " << tree.find_el(tree.root, 3, 1)->right->key << endl;

    tree.show_tree(tree.root);

    //tree.del_el(tree.root, 9, 1);
    tree.write_dot_file(tree.root, "tree1.dot");
    tree.del_el(tree.root, 10, 1);
    tree.del_el(tree.root, 10, 1);
    tree.del_el(tree.root, 10, 1);
    //tree.del_el(tree.root, 13, 1);
    tree.write_dot_file(tree.root, "tree2.dot");
    // cout << "__________________________"<<endl;
    // //cout << "key = " << tree.find_el(tree.root, 3, 2)->right->key << endl;
    // tree.show_tree(tree.root);
    // cout<< tree.find_min(tree.root)->key <<endl;

    //cout << tree.root->right->right->right->key << endl;

    return 0;

}
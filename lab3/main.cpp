#include <vector>
#include <iostream>
#include <string>
#include "ht.h"
using std::cout;
using std::endl;
using std::string;

int main(){
    
    int size1 = 10;
    int size2 = 10;
    Table table(size1, size2);

    table.insert_item(2, 0, "info", "k2", "info", "info");
    table.insert_item(1, 0, "info", "k2", "info", "info");
    table.insert_item(4, 0, "info", "k2", "info", "info");
    table.insert_item(5, 0, "info", "k2", "info", "info");
    table.insert_item(3, 0, "info", "k22", "info", "info");
    table.insert_item(3, 0, "info", "k222", "info", "info");
    table.insert_item(1, 0, "info", "k3", "info", "info");
    // table.insert_item(3, 0, "info", "k3", "info", "info");
    // table.insert_item(8, 0, "info", "k3", "info", "info");
    // table.insert_item(2, 0, "info", "k3", "info", "info");
    table.insert_item(2, 0, "info", "k33", "info", "info");
    table.insert_item(3, 0, "info", "k33", "info", "info");



    // table.show_table();
    // vector<Item> tt = table.find_item_key1(1);
    // cout << tt.size() << endl;
    // for (int i = 0; i < tt.size(); i++){
    //     cout << tt[i].pt_key1->key << " " << tt[i].pt_key2->key << endl;
    // }

    // table.del_item_by_key2("k22");
    //table.del_item_by_key2("k222");

    //cout << "jhjh" << endl;
    // table.del_item(2, "k2");
    // table.del_item(1, "k2");
    // table.del_item(4, "k2");
    // table.del_item(5, "k2");
    // table.del_item(3, "k22");
    // table.del_item(1, "k3");
    // table.del_item(3, "k3");
    //table.show_table();
    //cout << table.table_key2[7]->pt_item_key2->pt_key1<< endl;
    // table.append_key1(7, 0, "ghjk");
    // for(int i = 0; i < table.table_key1.size(); i++){
    //     cout << table.table_key1[i].busy << " " << table.table_key1[i].key << endl;
    // }
    // table.del_el_keyspace1(4);
    // table.del_el_keyspace1(7);
    // table.del_el_keyspace1(2);
    // table.del_el_keyspace1(1);
    // table.del_el_keyspace1(5);
    // table.del_el_keyspace1(3);
    // for(int i = 0; i < table.table_key1.size(); i++){
    //     cout << table.table_key1[i].busy << " " << table.table_key1[i].key << endl;
    // }
    // table.reorganize_keyspace1();
    // for(int i = 0; i < table.table_key1.size(); i++){
    //     cout << table.table_key1[i].busy << " " << table.table_key1[i].key << endl;
    // }
    // table.append_key1(8, 0, "poooh");
    // for(int i = 0; i < table.table_key1.size(); i++){
    //     cout << table.table_key1[i].busy << " " << table.table_key1[i].key << endl;
    // }
    return 0;
}
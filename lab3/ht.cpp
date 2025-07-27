#include <vector>
#include <iostream>
#include <string>
#include "ht.h"
using std::cout;
using std::endl;
using std::string;


void Table::del_el_keyspace1(int key1){
    int n = table_key1.size();
    for (int i = 0; i < n; i++){
        if (table_key1[i].key == key1 && table_key1[i].busy == 1){
            table_key1[i].busy = 0;
            return;
        }
    }
    cout << "There's no such element in keyspace1" << endl;
    return;
}

int Table::reorganize_keyspace1(){
    for (int j = 0; j < msize1; j++){
        int n = table_key1.size();
        for (int i = 0; i < n; i++){
            if(table_key1[i].busy == 0){
                table_key1.erase(table_key1.begin() + i);
                break;
            }
        }
        if (n == table_key1.size()){
            break;
        }
    }
    if (table_key1.size() == msize1) return 0;
    else return 1;
}

KeySpace1* Table::append_key1(int key1, int par, string info){
    cout << table_key1.size() << endl;
    if (table_key1.size() == msize1){
        if (reorganize_keyspace1() == 0){
            cout << "There's no free space for element" << endl;
            return nullptr;
        }
    }
    KeySpace1* pt_key1 = find_el_in_keyspace1(key1);
    KeySpace1* pt_par_key1 = find_el_in_keyspace1(par);
    if (pt_key1 == nullptr){
        if (pt_par_key1 != nullptr || par == 0){
            table_key1.push_back(KeySpace1 {1, key1, par, info});
            return &table_key1.back();
        }
        else{
            cout << "There is no such parent in keyspace1" << endl;
            return nullptr;
        }
    }
    else{
        cout << "There is such element in keyspace1, try again" << endl;
        return nullptr;
    }
}

KeySpace1* Table::find_el_in_keyspace1(int key){
    int n = table_key1.size();
    for (int i = 0; i < n; i++){
        if (table_key1[i].key == key && table_key1[i].busy == 1){
            return &table_key1[i];
        }
    }
    return nullptr;
}

unsigned Table::hash_function(string key2){
    unsigned i = 0;
    for (int j = 0; j < key2.length(); j++){
        i += key2[j];
    }
    return i % msize2;
}

KeySpace2* Table::find_el_in_keyspace2(string key2){
    int index = hash_function(key2);
    KeySpace2* obh = table_key2[index];
    while(obh != nullptr){
        if (obh->key == key2){
            return obh;
        }
        obh = obh->next;
    }
    return nullptr;
}

KeySpace2* Table::append_key2(string key2, string info){
    KeySpace2* pt_key2 = find_el_in_keyspace2(key2);
    if (find_el_in_keyspace2(key2) != nullptr){
        //cout << "There's such element in keyspace2 yet" << endl;
        return nullptr;
    }
    else{
        int index = hash_function(key2);
        KeySpace2* obh = table_key2[index];
        //cout << "ghjjl" << obh << "jjj" << endl;
        if (obh->key == ""){
            //cout << "ghjjl" << index << endl;
            obh->key = key2;
            obh->info = info;
            return obh;
        }
        else{
            while(obh->next != nullptr){obh = obh->next;}
            KeySpace2 *el_new =  new KeySpace2(key2, nullptr, info);
            obh->next = el_new;
            el_new->prev = obh;
            return obh->next;
        }
    }
}

void Table::del_el_keyspace2(string key2){
    if (find_el_in_keyspace2(key2) == nullptr){
        cout << "There's no such element in keyspace2" << endl;
        return;
    }
    else{
        int index = hash_function(key2);
        KeySpace2* obh = table_key2[index];
        if (obh->key == key2){
            KeySpace2* deleted = obh->next;
            obh->info = deleted->info;
            obh->key = deleted->key;
            obh->next = deleted->next;
            delete deleted;
            return;
        }
        while(obh != nullptr){
            if (obh->next->key == key2){
                KeySpace2* deleted = obh->next;
                obh->next = obh->next->next;
                delete deleted;
                return;
            }
            obh = obh->next;
        }
    }
}

void Table::insert_item(int key1, int par_key1, string info_key1, string key2, string info_key2, string info_item){
    KeySpace1* pt_key1 = append_key1(key1, par_key1, info_key1);
    KeySpace2* pt_key2 = append_key2(key2, info_key2);
    KeySpace1* pt_key1_f = find_el_in_keyspace1(key1);
    KeySpace2* pt_key2_f = find_el_in_keyspace2(key2);
    Item* obh = pt_key2_f->pt_item_key2;
    if ( find_item(key1, key2) == nullptr ){
        Item* new_item = new Item(info_item, pt_key1_f, pt_key2_f);
        int num = pt_key1_f->num_of_item;
        pt_key1_f->num_of_item = num + 1;
        cout << "new_item = " << pt_key1_f << endl;
        if (obh == nullptr) {
            pt_key2_f->pt_item_key2 = new_item; 
            cout << "kkkkk "<<pt_key2_f->pt_item_key2->pt_key1->key << endl;
        }
        else {
            while(obh->next != nullptr){
                obh = obh->next;
            }
            obh->next = new_item;
            new_item->prev = obh;
            cout << new_item->prev->pt_key1->key << endl;
        }
        return;
    }
    else{
        cout << "Where is such element with (key1, key2)" << endl;
        return;
    }
};

Item* Table::find_item(int key1, string key2){
    KeySpace2* ptr_key2 = find_el_in_keyspace2(key2);
    if (ptr_key2 == nullptr) {return nullptr;}
    else{
        if ( ptr_key2->pt_item_key2 != nullptr){
            Item* ptr_key1 = ptr_key2->pt_item_key2;
            while(ptr_key1->pt_key1->key != key1){
                if (ptr_key1->next != nullptr){
                    ptr_key1 = ptr_key1->next;
                }
                else {
                    return nullptr;
                }
            }
            return ptr_key1;
        }
        else return nullptr;
    }
};

void Table::del_item(int key1, string key2){
    KeySpace1* obh_key1 = find_el_in_keyspace1(key1);
    int num = obh_key1->num_of_item;
    Item* item = find_item(key1, key2);
    if (item != nullptr){
        if (item->prev != nullptr){
            if (item->next != nullptr) item->prev->next = item->next;
            else item->prev->next=nullptr;
            delete item;
            if (num == 1){
                del_el_keyspace1(key1);
            }
            else{
                obh_key1->num_of_item = num - 1;
            }
            return;
        }
        else{
            KeySpace2* obh_key2 = find_el_in_keyspace2(key2);
            if (item->next != nullptr) {
                obh_key2->pt_item_key2 = item->next;
                item->next->prev = nullptr;
            }
            else {
                //obh_key2->pt_item_key2 = nullptr;
                if (obh_key2->prev != nullptr) {
                    if (obh_key2->next != nullptr) {
                        obh_key2->prev->next = obh_key2->next;
                        obh_key2->next->prev = obh_key2->prev;
                        cout << obh_key2->key << endl;
                    }
                    else obh_key2->prev->next = nullptr;
                }
                else{
                    if ( obh_key2->next != nullptr){
                        //table_key2[hash_function(key2)] = obh_key2->next;
                        table_key2[hash_function(key2)]->pt_item_key2 = obh_key2->next->pt_item_key2;
                        table_key2[hash_function(key2)]->key = obh_key2->next->key;
                        table_key2[hash_function(key2)]->prev = nullptr;				
                        table_key2[hash_function(key2)]->next = obh_key2->next->next;	
                        table_key2[hash_function(key2)]->info =  obh_key2->next->info;
                        //obh_key2->next->prev = nullptr;
                        
                    }
                    else {
                        table_key2[hash_function(key2)]->pt_item_key2 = nullptr;
                        table_key2[hash_function(key2)]->key = "";
                        table_key2[hash_function(key2)]->prev = nullptr;				
                        table_key2[hash_function(key2)]->next = nullptr;	
                        table_key2[hash_function(key2)]->info = " ";
                    }
                } 
                delete obh_key2;
            }
            delete item;
            return;
        }
    }
    else{
        return;
    }
};

vector<Item> Table::find_item_key1(int key1){
    vector<Item> result;
    KeySpace2* obh = table_key2[0];
    for ( int i = 0; i < msize2; i++){
        obh = table_key2[i];
        while (obh->pt_item_key2 != nullptr){
            Item* obh_item = obh->pt_item_key2;
            if (obh_item->pt_key1->key == key1){result.push_back(Item {obh_item->info, obh_item->pt_key1, obh_item->pt_key2});}
            while (obh_item->next != nullptr){
                obh_item = obh_item->next;
                if (obh_item->pt_key1->key == key1){result.push_back(Item {obh_item->info, obh_item->pt_key1, obh_item->pt_key2});}
            }
            if (obh->next != nullptr){obh = obh->next;}
            else {break;}
        }

    }
    return result;
};

vector<Item> Table::find_item_key2(string key2){
    Item* ptr_item = find_el_in_keyspace2(key2)->pt_item_key2;
    vector<Item> result;
    while(ptr_item != nullptr){
        result.push_back(Item {ptr_item->info, ptr_item->pt_key1, ptr_item->pt_key2});
        ptr_item = ptr_item->next;
    }
    return result;
};

void Table::del_item_by_key1(int key1){
    KeySpace2* obh = table_key2[0];
    for (int i = 0; i < msize2; i++){
        obh = table_key2[i];
        while (obh != nullptr){
            if (obh->pt_item_key2 != nullptr){
                Item* obh_item = obh->pt_item_key2;
                if (obh_item->pt_key1->key == key1){del_item(key1, obh_item->pt_key2->key);}
                while (obh_item->next != nullptr){
                    obh_item = obh_item->next;
                    if (obh_item->pt_key1->key == key1){del_item(key1, obh_item->pt_key2->key);}
                }
            }
            if (obh->next != nullptr){obh = obh->next;}
            else {break;}
        }
    }
    return;
};

void Table::del_item_by_key2(string key2){

    Item* ptr_item = find_el_in_keyspace2(key2)->pt_item_key2;

    del_item(ptr_item->pt_key1->key, ptr_item->pt_key2->key);

    if (find_el_in_keyspace2(key2)!=nullptr){
        if (find_el_in_keyspace2(key2)->pt_item_key2 != nullptr){
            return del_item_by_key2(key2);
        }
    }
    else {
        return;
    }
};

void Table::show_table(){
    int i = 0;
    KeySpace2* obh = table_key2[0];
    for (i; i < msize2; i++){
        cout << " i = "<< i << endl;
        obh = table_key2[i];
        while (obh->pt_item_key2 != nullptr){
            Item* obh_item = obh->pt_item_key2;
            cout << "key1 = " << obh_item->pt_key1->key << " key2 = " << obh_item->pt_key2->key << endl;
            while (obh_item->next != nullptr){
                obh_item = obh_item->next;
                cout << "key1 = " << obh_item->pt_key1->key << " key2 = " << obh_item->pt_key2->key << endl;
            }
            if (obh->next != nullptr) obh = obh->next;
            else break;
        } 
    }
    return;
};

// Table::Table(const Table& other) : msize1(other.msize1), msize2(other.msize2) 
// {
//     table_key1.reserve(msize1);
//     table_key2 = new KeySpace2* [msize2];
//     for (int i = 0; i < msize2; i++)
//         table_key2[i] = new KeySpace2[1];
//     for (int i = 0; i < msize2; i++){

//     }
// }; 

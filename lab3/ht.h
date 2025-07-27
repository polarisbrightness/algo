#include <vector>
#include <iostream>
#include <string>
using std::string;
using std::vector;
using std::cout;
using std::endl;

struct KeySpace1;
struct Keyspace2;
struct Item;

struct KeySpace1{
    int busy;			
    int key;			
    int par;
    int num_of_item = 0;			
    string info;
    KeySpace1(int k_busy, int k_key, int k_par, string k_info): busy(k_busy), key(k_key), par(k_par), info(k_info){};
};
struct KeySpace2{
    Item* pt_item_key2 = nullptr;
    string key = "";
    KeySpace2* prev = nullptr;				
    KeySpace2 *next = nullptr;	
    string info = " ";
    KeySpace2(string k_key, KeySpace2* k_next, string k_info): key(k_key), next(k_next), info(k_info) {};
    KeySpace2(){};
};
struct Item{
    string  info;		
    KeySpace1* 	pt_key1;	
    KeySpace2* 	pt_key2;
    Item* next = nullptr;	
    Item* prev = nullptr;
    Item(string i_info, KeySpace1* i_key1, KeySpace2* i_key2): info(i_info), pt_key1(i_key1), pt_key2(i_key2){};
};

class Table{

    public:
    int 	msize1;
    int 	msize2;
    vector<KeySpace1> table_key1; 
    KeySpace2** table_key2 = nullptr;

    Table(int t_msize1, int t_msize2): msize1(t_msize1), msize2(t_msize2){
        table_key1.reserve(msize1);
        table_key2 = new KeySpace2* [msize2];
        for (int i = 0; i < msize2; i++)
            table_key2[i] = new KeySpace2[1];
        
    };

    //functions for table
    void insert_item(int key1, int par_key1, string info_key1, string key2, string info_key2, string info_item);
    Item* find_item(int key1, string key2);
    void del_item(int key1, string key2);
    vector<Item> find_item_key1(int key1);
    vector<Item> find_item_key2(string key2);
    void del_item_by_key1(int key1);
    void del_item_by_key2(string key2);
    void show_table();

    //functions for keyspace1
    void del_el_keyspace1(int key1);
    int reorganize_keyspace1();
    KeySpace1* append_key1(int key1, int par, string info);
    KeySpace1* find_el_in_keyspace1(int key);

    //functions for keyspace2
    unsigned hash_function(string key2);
    void del_el_keyspace2(string key2);
    KeySpace2* append_key2(string key2, string info);
    KeySpace2* find_el_in_keyspace2(string key2);

    ~Table(){
        KeySpace2* obh = nullptr;
        for (int i = 0; i < msize2; i++){
            obh = table_key2[i];
            cout << i << endl;
            while (obh->next != nullptr){
                cout << obh->next->key << endl;
                del_item_by_key2(obh->next->key);
                obh = table_key2[i];
            }
            delete [] table_key2[i];
        }
        delete [] table_key2;
    }
    /*Copy constructor*/
    Table(const Table& other) = delete;

    /*Operator =*/
    const Table& operator=(const Table other) = delete;

    /*Move constructor*/
    Table (Table&& move) noexcept = delete;

    /*Copy move constructor*/
    Table& operator=(Table&& right) noexcept = delete;
};


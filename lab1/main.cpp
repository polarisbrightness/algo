#include <iostream>
#include<ctime>
#include "matrix.h"

using std::cout;
using std::cin;
using std::endl;

int main(void)
{
    srand(time(NULL));

    unsigned m; 
    unsigned* ncols;
    cout<< "input m: ";
    cin >> m;
    ncols = new unsigned[m];
    for(int i = 0; i < m; i++){
        cout << "Input ncols ["<< i << "] : ";
        cin >> ncols[i];
    }

    try{
        Matrix m1(m, ncols);

        m1.fill_matrix();
        m1.show_matrix();
    
        cout << "m = " << m1.get_m() << endl;
    
        int *b = new int[m1.get_m()];
    
        Fillb(m1, b, m1.get_m(), true_false);
        ShowB(b, m1.get_m());
    
        delete [] b;
        delete [] ncols;
    
        return 0;
    }
    catch(const char* e){
        cout << e << endl;
        return 0;
    }
}
#include <iostream>
#include "matrix.h"

using std::cout;
using std::cin;
using std::endl;

void Matrix::alloc_mem()
{
    ncols = new unsigned[m];
    matrix = new int*[m];

    for (int i = 0; i < m; i++)
        matrix[i] = new int[ncols[i]];
}

void Matrix::free_mem()
{
    delete [] ncols;

    for (int i = 0; i < m; i++)
        delete [] matrix[i];

    delete [] matrix;
}

void Matrix::fill_ncols(const unsigned* columns)
{
    for (int i = 0; i < m; i++)
        ncols[i] = columns[i];  
}

void Matrix::set_matrix(int** mtx)
{
    for (int i = 0; i < m; i++){
        for (int j = 0; j < ncols[i]; j++)
            matrix[i][j] = mtx[i][j];
    }
}

void Matrix::setf_matrix(int (*fill)())
{
    for (int i = 0; i < m; i++){
        for (int j = 0; j < ncols[i]; j++)
            matrix[i][j] = fill();
    }
}

Matrix::Matrix(unsigned size, unsigned* columns) : m(size) 
{
    try{
        alloc_mem();
        fill_ncols(columns);
        setf_matrix(fill_matrix);
    }
    catch(const std::bad_alloc&){
        free_mem();

        throw "Error in memory allocation!";
    }
}

Matrix::Matrix(const Matrix& other) : m(other.m) 
{
    try{
        alloc_mem();
        fill_ncols(other.ncols);
        set_matrix(other.matrix);
    }
    catch(const std::bad_alloc&){
        free_mem();

        throw "Error in memory allocation!";
    }
} 

const Matrix& Matrix::operator=(const Matrix other)
{
    if (this == &other) // не присваиваем объект самому себе
        return *this;

    free_mem();
    
    m = other.m;

    try{
        alloc_mem();
        fill_ncols(other.ncols);
        set_matrix(other.matrix);
        
        return *this;
    }
    catch(const std::bad_alloc&){
        free_mem();
        throw "Error in memory allocation!";
    }
}

Matrix::Matrix (Matrix&& move) noexcept : m(move.m)
{
    ncols = move.ncols;
    matrix = move.matrix;

    move.ncols = nullptr;
    move.matrix = nullptr;
}

Matrix& Matrix::operator=(Matrix&& right) noexcept
{
    if (this == &right)
        return *this;
        
    free_mem();
    
    m = right.m;

    ncols = right.ncols;
    matrix = right.matrix;

    right.ncols = nullptr;
    right.matrix = nullptr;
    
    return *this;
}

void Matrix::show_matrix(){
    for(int i = 0; i < m; i++){
        for(int j = 0; j < ncols[i]; j++){
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

int Matrix::get_val(int i, int j) const 
{
    if (i >= m)
        return -1;
    if (j >= ncols[i])
        return -1;  
    return matrix[i][j];
}

Matrix::~Matrix(){
    cout << endl;
    for (int i = 0; i < m; i++){
        delete [] matrix[i];
        //cout << "matrix[" << i << "] deleted!" << endl;
    }
    delete [] matrix;
    //cout << "matrix deleted!" << endl;
    delete [] ncols;
    //cout << "ncols deleted!" << endl;
}

/*Functions*/

void Fillb(const Matrix matrix, int* b, int m, int f(int))
{
    int s1 = 0, s2 = 0;

    for (int i = 0; i < m; i++)
    {
        s1 = 0, s2 = 0;
        
        for (int j = 0; j < matrix.get_ncols(i); j++)
        {
            if (f(matrix.get_val(i, j))== 0)
                s1+=matrix.get_val(i, j);
            else
                s2+=matrix.get_val(i, j);
            
        }
        b[i] = s1 - s2;
    }
}

void ShowB(int* b, int m)
{
    for (int i = 0; i < m; i++)
        cout << "b[" << i << "] = " << b[i] << endl;
}

int true_false(int x)
{
    return x % 3 == 0; 
}
#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>

class Matrix
{
private:
    unsigned m = 0;
    unsigned* ncols = nullptr;  
    int **matrix = nullptr;

    void alloc_mem();
    void free_mem();
    void fill_ncols(const unsigned* columns);
    void set_matrix(int** mtx);
    void setf_matrix(int (*fill)());
public:
    /*Constructor*/
    Matrix(unsigned size, unsigned* columns);

    /*Copy constructor*/
    Matrix(const Matrix& other);

    /*Operator =*/
    const Matrix& operator=(const Matrix other);

    /*Move constructor*/
    Matrix (Matrix&& move) noexcept;

    /*Copy move constructor*/
    Matrix& operator=(Matrix&& right) noexcept;

    static int fill_matrix() { return rand()%10; }

    void show_matrix();

    int get_val(int i, int j) const;

    int get_ncols(int i) const { return ncols[i]; }

    int get_m() const {return m;}

    ~Matrix();
};

/*Functions*/

void Fillb(const Matrix, int*, int, int(*)(int));
void ShowB(int*, int);
int true_false(int);

#endif
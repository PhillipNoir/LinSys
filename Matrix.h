#ifndef MATRIX_H
#define MATRIX_H

#include <memory>

struct Matrix {
    int rows, cols;
    std::unique_ptr<std::unique_ptr<double[]>[]> matriz;

    Matrix(int r, int c);
    double& at(int fila, int col);
    void fillMatrix();
    void print();
};

#endif

#include "Matrix.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    matriz = std::make_unique<std::unique_ptr<double[]>[]>(rows);
    for (int i = 0; i < rows; ++i) {
        matriz[i] = std::make_unique<double[]>(cols);
    }
}

double& Matrix::at(int fila, int col) {
    if (fila < 0 || fila >= rows || col < 0 || col >= cols) {
        throw std::out_of_range("Índices fuera de rango");
    }
    return matriz[fila][col];
}

void Matrix::fillMatrix() {
    std::cout << "Ingrese los " << rows * cols << " elementos de la matriz:\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << "Ingrese el elemento (" << i << "," << j << "): ";
            std::cin >> matriz[i][j];
        }
    }
}

void Matrix::print() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << std::setw(10) << matriz[i][j] << " ";
        }
        std::cout << '\n';
    }
}

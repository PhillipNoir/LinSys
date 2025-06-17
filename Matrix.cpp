/**
 * @file Matrix.cpp
 * @brief Implementación de la clase Matrix para representar y manipular matrices dinámicas.
 * 
 * @section features_sec Características principales
 * -Esta estructura proporciona métodos para acceder, llenar e imprimir matrices, utilizando punteros inteligentes para una gestión segura de memoria dinámica lo que permite correrlo en cualquier equipo.
 * -Forma parte del módulo de resolución de sistemas de ecuaciones lineales.
 * @author [Sergio Felipe Gonzalez Cruz]
 * @date [11 de junio de 2025]
 * 
 */
#include "Matrix.hpp"
#include <iostream>
#include <iomanip>
#include <stdexcept>

/**
 * @brief Constructor de la clase Matrix.
 * 
 * Crea una matriz de dimensiones dadas, asignando memoria dinámica utilizando `std::unique_ptr`.
 * 
 * @param r Número de filas.
 * @param c Número de columnas.
 */
Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    matriz = std::make_unique<std::unique_ptr<double[]>[]>(rows);
    for (int i = 0; i < rows; i++) {
        matriz[i] = std::make_unique<double[]>(cols);
    }
}

int Matrix::getRows() const{
    return rows;
}

int Matrix::getCols() const{
    return cols;
}

/**
 * @brief Accede (con verificación de límites) a un elemento de la matriz.
 * 
 * Devuelve una referencia al elemento en la posición indicada. Lanza una excepción si los índices están fuera de rango.
 * 
 * @param row Fila del elemento.
 * @param col Columna del elemento.
 * @return double& Referencia al elemento solicitado.
 * 
 * @throw std::out_of_range Si los índices están fuera de los límites de la matriz.
 */
double& Matrix::at(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw std::out_of_range("Índices fuera de rango");
    }
    return matriz[row][col];
}

/**
 * @brief Llena la matriz con datos ingresados por el usuario desde consola.
 * 
 * Solicita cada elemento individualmente e imprime su posición para facilitar el ingreso.
 */
void Matrix::fillMatrix() {
    std::cout << "Ingrese los " << rows * cols << " elementos de la matriz:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; ++j) {
            std::cout << "Ingrese el elemento (" << i << "," << j << "): ";
            std::cin >> matriz[i][j];
        }
    }
}

/**
 * @brief Imprime la matriz en consola con formato.
 * 
 * Utiliza `std::setw` para alinear columnas y mostrar la matriz de forma legible.
 */
void Matrix::print() const{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << std::setw(10) << matriz[i][j] << " ";
        }
        std::cout << '\n';
    }
}

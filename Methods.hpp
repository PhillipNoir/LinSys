/**
 * @file Methods.h
 * @brief Declaración del método para resolver sistemas de ecuaciones lineales mediante eliminación de Gauss y Gauss-Jordan.
 * 
 * Este archivo contiene la declaración de la función `gaussElimination`, que implementa el algoritmo
 * de eliminación de Gauss con pivoteo parcial para resolver sistemas de ecuaciones lineales Ax = b y la función 'gaussJordanElimination' 
 * que impplementa el algoritmo de eliminación de Gauss-Jordan.
 * 
 * @author [Sergio Felipe Gonzalez Cruz]
 * @date [11 de junio de 2025]
 */
#ifndef METHODS_HPP
#define METHODS_HPP

#include "Matrix.hpp"
#include <vector>

/**
 * @brief Resuelve un sistema de ecuaciones lineales mediante el método de eliminación de Gauss con pivoteo parcial.
 * 
 * Esta función transforma la matriz A en una matriz triangular superior y luego resuelve el sistema mediante 
 * sustitución regresiva. Tanto la matriz A como el vector b se modifican en el proceso.
 * 
 * @param A Matriz cuadrada de coeficientes del sistema (modificada durante la ejecución).
 * @param b Vector columna de términos independientes (modificado durante la ejecución).
 * @return std::vector<double> Vector solución del sistema.
 * 
 * @throw std::runtime_error Si el sistema no tiene solución única.
 */
std::vector<double> gaussElimination(Matrix& A, Matrix& b, bool mostrarPasos);

std::vector<double> gaussJordanElimination(Matrix& A, Matrix&b, bool mostrarPasos);

void imprimirSistema(Matrix& A, Matrix& b);

#endif

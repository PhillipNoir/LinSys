/**
 * @file utils.cpp
 * @brief Modulacización de funciones que se repiten o pueden repetirse
 * 
 * Este archivo contiene la llamada de las funciones forwardElimination y backward elimination, las cuales, son usadas en los métodos
 * de solución de sistemas lineales implementados en este programa.
 */

#ifndef UTILS_HPP
#define UTILS_HPP

#include "Matrix.hpp"

/**
 * @brief Realiza la eliminación hacia adelante (triangulación) del sistema Ax = b.
 *
 * Esta función aplica el método de eliminación de Gauss para convertir la matriz A
 * en una forma triangular superior, modificando también el vector columna b.
 * Detecta sistemas inconsistentes o numéricamente inestables.
 *
 * @param A Matriz de coeficientes (modificada en el proceso).
 * @param b Vector columna de términos independientes (modificado en el proceso).
 * @param mostrarPasos Si es verdadero, imprime cada paso si el sistema es pequeño (≤ 10 ecuaciones).
 *
 * @throws std::runtime_error Si el sistema es numéricamente inestable o inconsistente.
 */
void forwardElimination(Matrix& A, Matrix& b, bool mostrarPasos);

/**
 * @brief Realiza la eliminación hacia atrás y normalización de pivotes en la matriz A.
 *
 * Esta función convierte A en una matriz identidad (forma reducida por filas) mediante
 * eliminación hacia atrás y normalización de pivotes. Es el paso final del método de Gauss-Jordan.
 *
 * @param A Matriz de coeficientes (modificada).
 * @param b Vector columna de términos independientes (modificado).
 * @param mostrarPasos Si es verdadero, imprime los pasos si el sistema es pequeño.
 *
 * @throws std::runtime_error Si se detectan pivotes demasiado pequeños o inconsistencias numéricas.
 */
void backwardElimination(Matrix& A, Matrix& b, bool mostrarPasos);
#endif
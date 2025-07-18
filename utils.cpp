/**
 * @file utils.cpp
 * @brief Modularización de funciones que se repiten o pueden repetirse
 * 
 * Este archivo contiene la declaración de las funciones forwardElimination y backward elimination, las cuales, son usadas en los métodos
 * de solución de sistemas lineales implementados en este programa.
 */
#include "Matrix.hpp"
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "Methods.hpp"
#include "String.hpp"


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
void forwardElimination(Matrix& A, Matrix& b, bool mostrarPasos) {
    int numEcuations = A.getRows();
    bool mostrar = mostrarPasos && numEcuations <= 10;
    const double TOLERANCIA = 1e-12;

    for (int column = 0; column < numEcuations; column++) {
        // 1. Encontrar fila con el mayor pivote
        int maxRow = column; //Al inicio la fila con el pivote máximo será la primera ingresada por el usuario
        //Recorremos cada fila para ver si hay una fila con pivote mayor
        for (int row = column + 1; row < numEcuations; row++) {
            //Si encontramos una fila con un pivote mayor, esa fila será la nueva fila con el pivote máximo
            if (std::abs(A.at(row, column)) > std::abs(A.at(maxRow, column))) {
                maxRow = row;
            }
        }

        // 2. Verificar si hay solución
        if (std::abs(A.at(maxRow, column)) < TOLERANCIA) {
            throw std::runtime_error("El sistema es numéricamente inestable o no tiene solución única.");
        }

        // 3. Intercambiar filas en A y b si es necesario
        if (maxRow != column) {
            //Este ciclo intercambia los valores de las filas posición por posición, no toda la fila de golpe.
            for (int col = 0; col < numEcuations; col++) {
                std::swap(A.at(column, col), A.at(maxRow, col));
            }
            //Al ser una matriz de una dimensión solo es necesario intecambiar un valor
            std::swap(b.at(column, 0), b.at(maxRow, 0));
            if (mostrar) {
                std::cout << "\nIntercambio de fila " << column << " con fila " << maxRow << ":\n";
                imprimirSistema(A, b);
            }
        }

        // 4. Eliminar hacia abajo
        //El ciclo inicia para modificar la segunda fila
        for (int row = column + 1; row < numEcuations; row++) {
            //Se calcula el factor que al multiplicarlo por la fila anterior y restarlo de la entrada correspondiente transforma en 0 la entrada correspondiente
            double factor = A.at(row, column) / A.at(column, column);
            for (int col = column; col < numEcuations; col++) {
                A.at(row, col) -= factor * A.at(column, col);
            }
            //Al ser una matriz de una dimensión solo es necesario modificar un valor
            b.at(row, 0) -= factor * b.at(column, 0);

            if (mostrar) {
                std::cout << "\nEliminando fila " << row << " usando fila " << column << " (factor = " << factor << "):\n";
                imprimirSistema(A, b);
            }
        }
    }
    // 5. Verificación de filas nulas para detectar inconsistencia
    for (int row = 0; row < numEcuations; ++row) {
        bool filaNula = true;
        for (int col = 0; col < numEcuations; ++col) {
            if (std::abs(A.at(row, col)) > TOLERANCIA) {
                filaNula = false;
                break;
            }
        }
        if (filaNula && std::abs(b.at(row, 0)) > TOLERANCIA) {
            throw std::runtime_error("El sistema es inconsistente: no tiene solución.");
        }
    }
}


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
void backwardElimination(Matrix& A, Matrix& b, bool mostrarPasos){
    //Eliminar hacia atrás
    int numEcuations = A.getRows();
    bool mostrar = mostrarPasos && numEcuations <= 10;
    const double TOLERANCIA = 1e-12;

    //El ciclo inicia para modificar la última fila
    for (int column = numEcuations - 1; column >= 0; column--) {
        for (int row = column - 1; row >= 0; row--) {
            double factor = A.at(row, column) / A.at(column, column);
            for (int col = 0; col < numEcuations; col++) {
                A.at(row, col) -= factor * A.at(column, col); //Se usa toda la fila 'column'
            }
            b.at(row, 0) -= factor * b.at(column, 0); //Se usa el valor correspondiente de b
        }
        if (mostrarPasos) {
            std::cout << "Después de eliminar hacia arriba en columna " << column << ":\n";
            imprimirSistema(A, b);
    }

    // Normalización de pivotes (hacerlos 1)
    for (int rows = 0; rows < numEcuations; rows++) {
        double pivot = A.at(rows, rows);
        if (std::abs(pivot) < TOLERANCIA) {
            throw std::runtime_error("Pivote demasiado pequeño, posible sistema incompatible o mal condicionado.");
        }
        if (std::abs(pivot - 1.0) > TOLERANCIA) {
            for (int col = 0; col < numEcuations; col++) {
                A.at(rows, col) /= pivot;
            }
            b.at(rows, 0) /= pivot;
        }
        if (mostrarPasos) {
            std::cout << "Normalizando fila " << rows << ":\n";
            imprimirSistema(A, b);
        }
        }
    }
}

/**
 * @brief Método iterativo generalizado para Jacobi y Gauss-Seidel.
 * Este método permite resolver sistemas de ecuaciones lineales utilizando
 * tanto el método de Jacobi como el de Gauss-Seidel, dependiendo del parámetro
 * `usarValoresActuales`.
 * @param A Matriz de coeficientes del sistema (no se modifica).
 * @param b Vector columna de términos independientes (no se modifica).
 * @param tolerancia Criterio de parada para la convergencia (por defecto 1e-6).
 * @param maxIter Número máximo de iteraciones permitidas (por defecto 500).
 * @param usarValoresActuales Si es true, utiliza el método de Gauss-Seidel; si es false, utiliza Jacobi.
 * @return Matrix Vector solución del sistema.
 */
Matrix metodoIterativoGeneral(Matrix& A, Matrix& b, double tolerancia, int maxIter, bool usarValoresActuales) {
    int n = A.getRows();
    const double TOLERANCIA_DIAGONAL = 1e-12;
    for (int i = 0; i < n; ++i) {
        if (std::abs(A.at(i, i)) < TOLERANCIA_DIAGONAL) {
            String pos; pos.fromInt(i);
            String msg = String("Cero en la diagonal principal en (") + pos + String(",") + pos + String(").");
            throw std::runtime_error(msg.c_str());
        }
    }
    Matrix x(n, 1), xPrev(n, 1);
    for (int i = 0; i < n; ++i) x.at(i,0) = xPrev.at(i,0) = 0.0;

    for (int iter = 0; iter < maxIter; ++iter) {
        for (int i = 0; i < n; ++i) xPrev.at(i,0) = x.at(i,0);
        double error = 0.0;
        for (int i = 0; i < n; ++i) {
            double suma = 0.0;
            for (int j = 0; j < n; ++j) {
                if (j == i) continue;
                if (usarValoresActuales && j < i)
                    suma += A.at(i, j) * x.at(j, 0); // Gauss-Seidel: usa el valor ya actualizado
                else
                    suma += A.at(i, j) * xPrev.at(j, 0); // Jacobi: usa el valor anterior
            }
            double nuevo = (b.at(i, 0) - suma) / A.at(i, i);
            error = std::max(error, std::abs(nuevo - x.at(i,0)));
            x.at(i,0) = nuevo;
        }
        if (error < tolerancia) return x;
    }
    String maxIterStr; maxIterStr.fromInt(maxIter);
    String msg = String("El método no convergió en ") + maxIterStr + String(" iteraciones.");
    throw std::runtime_error(msg.c_str());
}
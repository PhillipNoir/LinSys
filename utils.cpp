#include "Matrix.hpp"
#include <vector>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "Methods.hpp"

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
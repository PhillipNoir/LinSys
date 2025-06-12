/**
 * @file Methods.cpp
 * @brief Implementación de diferentes métodos numéricos para resolver sistemas de ecuaciones lineales.
 * 
 * @section features_sec Características principales.
 * -Método de eliminación de Gauss.
 * -Método de Gauss-Jordan (Por implementar).
 * -Método de LU (Por implementar).
 * -Método de QR (Por implementar).
 * -Método de mínimos cuadrados(Por implementar).
 * 
 * @author [Sergio Felipe Gonzalez Cruz]
 * @date [11 de junio de 2025]
 */

#include "Methods.h"
#include "Matrix.h"
#include <vector>
#include <stdexcept>
#include <cmath>

/**
 * @brief Resuelve un sistema de ecuaciones lineales mediante el método de eliminación de Gauss con pivoteo parcial.
 * 
 * Este método transforma la matriz A en una matriz triangular superior utilizando eliminación hacia adelante,
 * luego resuelve el sistema triangular resultante mediante sustitución regresiva.
 * 
 * @param A Matriz de coeficientes del sistema (modificada durante la ejecución).
 * @param b Vector columna de términos independientes (modificado durante la ejecución).
 * @return std::vector<double> Vector solución del sistema.
 * 
 * @throw std::runtime_error Si el sistema no tiene solución única (pivote cero en la diagonal).
 */

std::vector<double> gaussElimination(Matrix& A, Matrix& b) {
    int numEcuations = A.rows;

    // Eliminación hacia adelante
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

        // 2. Intercambiar filas en A y b si es necesario
        if (A.at(maxRow, column) == 0) {
            //Si hay más ecuaciones que incógnitas, el sistema está sobredeterminado y no tiene solución
            throw std::runtime_error("El sistema no tiene solución única o no tiene solución.");
        }
            //Si la fila con pivote máximo es diferente a la fila superior inicial se intercambian los lugares de las filas
        if (maxRow != column) {
            //Este ciclo intercambia los valores de las filas posición por posición, no toda la fila de golpe.
            for (int col = 0; col < numEcuations; col++) {
                std::swap(A.at(column, col), A.at(maxRow, col));
            }
            //Al ser una matriz de una dimensión solo es necesario intecambiar un valor
            std::swap(b.at(column, 0), b.at(maxRow, 0));
        }

        // 3. Eliminar hacia abajo
        //El ciclo inicia para modificar la segunda fila
        for (int row = column + 1; row < numEcuations; row++) {
            //Se calcula el factor que al multiplicarlo por la fila anterior restarlo de la entrada correspondiente transforma en 0 la entrada correspondiente
            double factor = A.at(row, column) / A.at(column, column);
            for (int col = column; col < numEcuations; col++) {
                A.at(row, col) -= factor * A.at(column, col);
            }
            //Al ser una matriz de una dimensión solo es necesario modificar un valor
            b.at(row, 0) -= factor * b.at(column, 0);
        }
    }

    // Sustitución regresiva
    std::vector<double> vectorSolucion(numEcuations);
    for (int row = numEcuations - 1; row >= 0; row--) {
        //Suma de los elementos ya conocidos
        double sum {0.0};
        //Este ciclo se activa si columna es menor al numero de ecuaciones, lo que nos dice que hay valor a la derecha
        for (int col = row + 1; col < numEcuations; col++) {
            //Se suma la multiplicación del coeficiente por el valor que ya conocemos, lo hace para todos los valores ya conocidos
            sum += A.at(row, col) * vectorSolucion[col];
        }
        //Despeja la variable desconocida pasando la suma como resta y el coeficiente como cosciente para resolver la incógnita y almacena el resultado en el último espacio libre del vector para que se acomoden de forma ordenada
        vectorSolucion[row] = (b.at(row, 0) - sum) / A.at(row, row);
    }
    //Retorna el vector solución
    return vectorSolucion;

}

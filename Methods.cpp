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
#include <iostream>
#include <iomanip>

/**
 * @brief Imprime el sistema de ecuaciones lineales en forma matricial.
 *
 * Esta función muestra en consola la matriz de coeficientes `A` y el vector de constantes `b` 
 * en forma de sistema ampliado (matriz aumentada), alineando los valores para mayor legibilidad.
 * 
 * Por ejemplo, imprime una salida como esta:
 * @code
 *        2         -1         3 |         9
 *        1          0        -2 |         3
 * @endcode
 *
 * @param A Matriz de coeficientes del sistema de ecuaciones (tipo Matrix).
 * @param b Vector columna con los términos independientes (tipo Matrix).
 */
void imprimirSistema(Matrix& A, Matrix& b) {
    for (int i = 0; i < A.rows; ++i) {
        for (int j = 0; j < A.cols; ++j) {
            std::cout << std::setw(10) << A.at(i, j) << " ";
        }
        std::cout << "| " << std::setw(10) << b.at(i, 0) << std::endl;
    }
    std::cout << std::endl;
}


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
std::vector<double> gaussElimination(Matrix& A, Matrix& b, bool mostrarPasos) {
    int numEcuations = A.rows;
    bool mostrar = mostrarPasos && numEcuations <= 10;

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
            if (mostrar)
            {
                std::cout<<"\nIntercambio de fila "<<column<<" con fila "<< maxRow << ":\n";
                imprimirSistema(A, b);
            }
        }

        // 3. Eliminar hacia abajo
        //El ciclo inicia para modificar la segunda fila
        for (int row = column + 1; row < numEcuations; row++) {
            //Se calcula el factor que al multiplicarlo por la fila anterior y restarlo de la entrada correspondiente transforma en 0 la entrada correspondiente
            double factor = A.at(row, column) / A.at(column, column);
            for (int col = column; col < numEcuations; col++) {
                A.at(row, col) -= factor * A.at(column, col);
            }
            //Al ser una matriz de una dimensión solo es necesario modificar un valor
            b.at(row, 0) -= factor * b.at(column, 0);
            if (mostrar)
            {
                std::cout<<"\nEliminando fila " << row << " usando fila "<< column << "(factor = " << factor <<"):\n";
                imprimirSistema(A, b);
            }
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

/**
 * @brief Resuelve un sistema de ecuaciones lineales mediante el método de eliminación de Gauss-Jordan con pivoteo parcial.
 * 
 * Este método transforma la matriz A en una matriz diagonal utilizando eliminación hacia adelante y atrás,
 * lo que nos entrega el vector solución de forma directa.
 * 
 * @param A Matriz de coeficientes del sistema (modificada durante la ejecución).
 * @param b Vector columna de términos independientes (modificado durante la ejecución).
 * @return std::vector<double> Vector solución del sistema.
 * 
 * @throw std::runtime_error Si el sistema no tiene solución única (pivote cero en la diagonal).
 */
std::vector<double> gaussJordanElimination(Matrix& A, Matrix& b, bool mostrarPasos){
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
            if (mostrarPasos) {
                std::cout << "Intercambio fila " << column << " con fila " << maxRow << ":\n";
                imprimirSistema(A, b);
            } 
        }

        // 3. Eliminar hacia abajo
        //El ciclo inicia para modificar la segunda fila
        for (int row = column + 1; row < numEcuations; row++) {
            //Se calcula el factor que al multiplicarlo por la fila anterior y restarlo de la entrada correspondiente transforma en 0 la entrada correspondiente
            double factor = A.at(row, column) / A.at(column, column);
            for (int col = column; col < numEcuations; col++) {
                A.at(row, col) -= factor * A.at(column, col);
            }
            //Al ser una matriz de una dimensión solo es necesario modificar un valor
            b.at(row, 0) -= factor * b.at(column, 0);
        }
        if (mostrarPasos) {
            std::cout << "Después de eliminar hacia abajo en columna " << column << ":\n";
            imprimirSistema(A, b);
        }
        
    }

    //Eliminar hacia atrás
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
        if (pivot == 0) {
            throw std::runtime_error("Pivote nulo detectado, sistema incompatible o mal condicionado.");
        }
        for (int col = 0; col < numEcuations; col++) {
            A.at(rows, col) /= pivot;
        }
        b.at(rows, 0) /= pivot;
        if (mostrarPasos) {
            std::cout << "Normalizando fila " << rows << ":\n";
            imprimirSistema(A, b);
        }
        }
    }

    //Guardado del vector solución
    std::vector<double> vectorSolucion(numEcuations);
    for (int sol = 0; sol < numEcuations; sol++)
    {
        vectorSolucion[sol] = b.at (sol, 0);
    }
    
    return vectorSolucion;
}
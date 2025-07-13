/**
 * @file Methods.cpp
 * @brief Implementación de diferentes métodos numéricos para resolver sistemas de ecuaciones lineales.
 * 
 * @section features_sec Características principales.
 * -Método de eliminación de Gauss.
 * -Método de Gauss-Jordan.
 * 
 */
#include "Methods.hpp"
#include "Matrix.hpp"
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "utils.hpp"
#include <string>

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
    int rows = A.getRows();
    int cols = A.getCols();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
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
 * @return Matrix vectorSolución solución del sistema.
 * 
 * @throw std::runtime_error Si el sistema no tiene solución única (pivote cero en la diagonal).
 */
Matrix gaussElimination(Matrix& A, Matrix& b, bool mostrarPasos) {
    forwardElimination(A, b, mostrarPasos);

    // Sustitución regresiva
    int numEcuations = A.getRows();
    Matrix vectorSolucion(numEcuations, 1);
    const double TOLERANCIA = 1e-12;

    for (int row = numEcuations - 1; row >= 0; row--) {
        //Suma de los elementos ya conocidos
        double sum {0.0};
        //Este ciclo se activa si columna es menor al numero de ecuaciones, lo que nos dice que hay valor a la derecha
        for (int col = row + 1; col < numEcuations; col++) {
            //Se suma la multiplicación del coeficiente por el valor que ya conocemos, lo hace para todos los valores ya conocidos
            sum += A.at(row, col) * vectorSolucion.at(col, 0);
        }
        
        double denom = A.at(row, row);
        
        //Envía un mensaje de error donde ocurre una división por cero durante la sustitución regresiva para evitar bugs o que el programa se rompa.
        if (std::abs(denom) < TOLERANCIA) {
            throw std::runtime_error("División por cero o sistema mal condicionado en sustitución regresiva.");
        }

        //Despeja la variable desconocida pasando la suma como resta y el coeficiente como cosciente para resolver la incógnita y almacena el resultado en el último espacio libre del vector para que se acomoden de forma ordenada
        vectorSolucion.at(row, 0) = (b.at(row, 0) - sum) / A.at(row, row);
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
 * @return Matrix vectorSolución solución del sistema.
 * 
 * @throw std::runtime_error Si el sistema no tiene solución única (pivote cero en la diagonal).
 */
Matrix gaussJordanElimination(Matrix& A, Matrix& b, bool mostrarPasos){
    forwardElimination(A, b, mostrarPasos);

    backwardElimination(A, b, mostrarPasos);

    int numEcuations = A.getRows();
    const double TOLERANCIA = 1e-10;

    for (int row = 0; row < numEcuations; row++) {
        for (int col = 0; col < numEcuations; col++) {
            if ((row == col && std::abs(A.at(row, col) - 1.0) > TOLERANCIA) || (row != col && std::abs(A.at(row, col)) > TOLERANCIA)) {
                throw std::runtime_error("La matriz no se redujo completamente a la identidad. El sistema puede estar mal condicionado.");
            }
        }
    }

    //Guardado del vector solución
    Matrix vectorSolucion(numEcuations, 1);
    for (int sol = 0; sol < numEcuations; sol++)
    {
        vectorSolucion.at(sol, 0) = b.at(sol, 0);
    }
    
    return vectorSolucion;
}

/**
 * @brief Resuelve un sistema de ecuaciones lineales mediante el método iterativo de Jacobi.
 * 
 * Este método utiliza iteraciones sucesivas para aproximar la solución del sistema Ax = b.
 * Requiere que la matriz A tenga diagonal dominante para garantizar convergencia.
 * 
 * @param A Matriz de coeficientes del sistema (no se modifica).
 * @param b Vector columna de términos independientes (no se modifica).
 * @param mostrarPasos Si true, muestra el progreso de las iteraciones.
 * @param tolerancia Criterio de parada para la convergencia (por defecto 1e-6).
 * @param maxIteraciones Número máximo de iteraciones permitidas (por defecto 1000).
 * @return std::vector<double> Vector solución del sistema.
 * 
 * @throw std::runtime_error Si hay ceros en la diagonal o no converge.
 */
Matrix jacobiMethod(Matrix& A, Matrix& b, double tolerancia, int maxIteraciones) {
    int numEquations = A.getRows();
    const double TOLERANCIA_DIAGONAL = 1e-12;
    
    
    // Verificar que no hay ceros en la diagonal
    for (int i = 0; i < numEquations; ++i) {
        if (std::abs(A.at(i, i)) < TOLERANCIA_DIAGONAL) {
            throw std::runtime_error("Cero en la diagonal principal en posición (" + std::to_string(i) + "," + std::to_string(i) + "). El método de Jacobi no puede continuar.");
        }
    }
    
    // Inicializar el vector solución y el vector solución anterior
    Matrix vectorSolucion(numEquations, 1);
    Matrix vectorSolucionAnterior(numEquations, 1);
    
    // Inicializar los vectores solución con ceros
    // Esto asegura que los vectores tengan el tamaño correcto y estén listos para las iteraciones
    for (int i = 0; i < numEquations; ++i) {
        vectorSolucion.at(i, 0) = 0.0;
        vectorSolucionAnterior.at(i, 0) = 0.0;
    }

    for (int iter = 0; iter < maxIteraciones; ++iter) {
        //Se copia el vector solución actual al vector solución anterior para calcular el error
        for (int i = 0; i < numEquations; ++i) {
            vectorSolucionAnterior.at(i, 0) = vectorSolucion.at(i, 0);
        }
        
        // Calcular nueva aproximación
        for (int i = 0; i < numEquations; ++i) {
            double suma = 0.0;
            
            for (int j = 0; j < numEquations; ++j) {
                if (i != j) {
                    suma += A.at(i, j) * vectorSolucionAnterior.at(j, 0);
                }
            }
            
            vectorSolucion.at(i,0) = (b.at(i, 0) - suma) / A.at(i, i);
        }
        
        // Calcular error máximo
        double error = 0.0;
        for (int i = 0; i < numEquations; ++i) {
            error = std::max(error, std::abs(vectorSolucion.at(i,0) - vectorSolucionAnterior.at(i,0)));
        }
        
        // Verificar convergencia
        if (error < tolerancia) {
                std::cout << "\n¡Convergencia alcanzada en " << iter + 1 << " iteraciones!" << std::endl;
                std::cout << "Error final: " << std::scientific << error << std::endl;
            return vectorSolucion;
        }
    }
    
    throw std::runtime_error("El método de Jacobi no convergió en " + std::to_string(maxIteraciones) + " iteraciones. " + "Verifique que la matriz tenga diagonal dominante.");
}

/**
 * @brief Implementa el método iterativo de Gauss-Seidel para resolver un sistema de ecuaciones lineales.
 * Este método mejora la aproximación de la solución en cada iteración utilizando los valores más recientes disponibles.
 * @param A Matriz de coeficientes del sistema (no se modifica).
 * @param b Vector columna de términos independientes (no se modifica).
 * @param tolerancia Criterio de parada para la convergencia (por defecto 1e-6).
 * @param maxIter Número máximo de iteraciones permitidas (por defecto 1000).
 * @return std::vector<double> Vector solución del sistema.
 * @throw std::runtime_error Si hay ceros en la diagonal principal o si no converge.
 */
Matrix gaussSeidelMethod(Matrix& A, Matrix& b, double tolerancia, int maxIter) {
    // Verificar que no hay ceros en la diagonal
    int numEquations = A.getRows();
    const double TOLERANCIA_DIAGONAL = 1e-12;
    for (int i = 0; i < numEquations; ++i) {
        if (std::abs(A.at(i, i)) < TOLERANCIA_DIAGONAL) {
            throw std::runtime_error("Cero en la diagonal principal en posición (" + std::to_string(i) + "," + std::to_string(i) + "). El método no puede continuar.");
        }
    }
    // Inicializar el vector solución y el vector solución copia
    Matrix vectorSolucion(numEquations, 1);
    Matrix vectorSolucionCopia(numEquations, 1);

    // Inicializar los vectores solución con ceros
    // Esto asegura que los vectores tengan el tamaño correcto y estén listos para las iteraciones
    for (int i = 0; i < numEquations; ++i) {
        vectorSolucion.at(i, 0) = 0.0;
        vectorSolucionCopia.at(i, 0) = 0.0;
    }
    for (int iteracion = 1; iteracion <= maxIter; ++iteracion) {
        double error = 0.0;
        for (int i = 0; i < numEquations; ++i) {
            double suma = 0.0;
            double vector_i_anterior = vectorSolucion.at(i, 0);
            for (int j = 0; j < numEquations; ++j) {
                if (j != i) {

                    if (j < i) {
                        suma += A.at(i, j) * vectorSolucion.at(j, 0);
                    }
                    else if (j > i) {
                        suma += A.at(i, j) * vectorSolucionCopia.at(j, 0);
                    }
                }
            }
            vectorSolucion.at(i, 0) = (b.at(i, 0) - suma) / A.at(i, i);
            double diferencia = std::abs(vectorSolucion.at(i,0) - vector_i_anterior);
            if (diferencia > error) {
                error = diferencia;
            }
        }
        
        if (error < tolerancia) {
            
            std::cout << "Convergencia alcanzada en iteración " << iteracion << std::endl;
            
            return vectorSolucion;
        }
        // Copiar el vector solución actual al vector copia para la próxima iteración
        for (int i = 0; i < numEquations; ++i) {
            vectorSolucionCopia.at(i, 0) = vectorSolucion.at(i, 0);
        }
    }
    
    throw std::runtime_error("El método de Gauss-Seidel no convergió en " + std::to_string(maxIter) + " iteraciones. Verifique que la matriz tenga diagonal dominante.");
    
    return vectorSolucion;
}
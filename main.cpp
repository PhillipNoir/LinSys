/**
 * @file main.cpp
 * @brief Punto de entrada del programa para resolver un sistema de ecuaciones lineales usando eliminación de Gauss.
 * 
 * @section features_sec Características Principales
 * - Llenado manual del sistema, lo que permite una personalización total para el problema que desee el usuario
 * - Uso de arreglos dinámicos para la creación y manipulación de matrices, lo que permite correr el programa en cualquier equipo
 * - Elección del método libre para el usuario
 * - Interfaz de menú intuitiva
 * 
 *  @section usage_sec Modo de Uso
 * 1. Ejecutar el programa
 * 2. Llenar la matriz
 * 3. Seleccionar el método de resolución
 * 4. Se retorna la matriz de resultado
 * 
 * @author [Sergio Felipe Gonzalez Cruz]
 * @date [5 de junio de 2025]
 * @version [0.0.3]
 */
#include "Matrix.h"
#include "Methods.h"
#include <iostream>
#include <iomanip>

/**
 * @brief Función principal del programa.
 * 
 * Solicita al usuario el tamaño del sistema, la matriz de coeficientes A y el vector de constantes b.
 * Luego aplica el método de eliminación gaussiana o Gauss-Jordan para resolver el sistema e imprime el vector solución.
 * 
 * @return int Código de salida del programa (0 si finaliza correctamente).
 */
int main() {
    int size;
    std::cout << "Bienvenido, ingrese el tamaño del sistema: ";
    std::cin >> size;

    // Crear matriz de coeficientes A y vector b

    Matrix A(size, size);
    Matrix b(size, 1);

    // Llenar A y b con datos ingresados por el usuario

    std::cout << "Ingrese la matriz A:\n";
    A.fillMatrix();

    std::cout << "Ingrese el vector b:\n";
    b.fillMatrix();

    bool mostrarPasos{true};
    

    // Resolver el sistema usando eliminación gaussiana

    std::vector<double> solution = gaussElimination(A, b, mostrarPasos);

    //Resolver usando Gauss-Jordan

    std::vector<double> solution = gaussJordanElimination(A, b, mostrarPasos);


    // Imprimir el vector solución

    std::cout << "Solución:\n";
    
    for (double val : solution) {
        std::cout << std::setw(10) << val << " ";
    }

    return 0;
}

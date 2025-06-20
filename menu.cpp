/**
 * @file menu.cpp
 * @brief Muestra el menú principal del programa y gestiona la interacción con el usuario.
 * 
 * Permite al usuario resolver sistemas de ecuaciones lineales utilizando los métodos de:
 * - Eliminación de Gauss
 * - Eliminación de Gauss-Jordan
 * 
 * El usuario puede:
 * - Ingresar el tamaño del sistema
 * - Proporcionar los coeficientes (matriz A) y el vector independiente (b)
 * - Elegir si desea ver los pasos intermedios de la solución
 * - Ver el resultado del sistema resuelto
 * - Salir del programa
 * 
 * La función se ejecuta en un bucle hasta que el usuario selecciona la opción de salir.
 * @author [Sergio Felipe Gonzalez Cruz]
 * @date [15 de junio de 2025]
 */
#include "Matrix.hpp"
#include "Methods.hpp"
#include <iostream>
#include <iomanip>
#include "menu.hpp"
#include "validations.hpp"
#include <string>

void menuPrincipal(){
    int opcion {0};
    bool continuar {true};

    std::cout<<"¡Bienvenido al resolvedor de sistemas de ecuaciones lineales!\n";
    
    int size{0};
    bool mostrarPasos{true};

    while (continuar)
    {
        std::cout<<"\nPor favor, elija el método por el cual deseas resolver tu sistema de ecuaciones lineales o selecciona la opción 'Salir' para terminar el programa: \n";
        std::cout << "\n1. Método de Gauss\n";
        std::cout << "2. Método de Gauss-Jordan\n";
        std::cout << "3. Salir\n";
        opcion = leerEntero("Su elección: ");
        std::cout << "Entrada registrada como " << opcion << " (cualquier parte decimal fue ignorada en caso de haber sido ingresada).\n";

        switch (opcion)
        {
        case 1: {
            size = leerEntero("\nIngrese el tamaño de la matriz: ");
            std::cout << "Entrada registrada como " << size << " (cualquier parte decimal fue ignorada en caso de haber sido ingresada).\n";
            Matrix A(size, size);
            Matrix b (size, 1);
            std::cout << "\nIngrese la matriz A:\n";
            A.fillMatrix();
            std::cout << "\nIngrese el vector b:\n";
            b.fillMatrix();
            mostrarPasos = leerBooleano("\n¿Desea ver los pasos de la solución? (Y:1/N:0)\n");
            std::vector<double> solution = gaussElimination(A, b, mostrarPasos);
            advertenciaSistemaGrande(size);
            std::cout << "Solución:\n";
    
            for (double val : solution) {
                std::cout << std::setw(10) << val << " ";
            }
            break;
        }
        case 2: {
            size = leerEntero("\nIngrese el tamaño de la matriz: ");
            std::cout << "Entrada registrada como " << size << " (cualquier parte decimal fue ignorada en caso de haber sido ingresada).\n";
            Matrix A(size, size);
            Matrix b (size, 1);
            std::cout << "\nIngrese la matriz A:\n";
            A.fillMatrix();
            std::cout << "\nIngrese el vector b:\n";
            b.fillMatrix();
            mostrarPasos = leerBooleano("\n¿Desea ver los pasos de la solución? (Y:1/N:0)\n");
            std::vector<double> solution = gaussJordanElimination(A, b, mostrarPasos);
            advertenciaSistemaGrande(size);
            std::cout << "Solución:\n";
    
            for (double val : solution) {
                std::cout << std::setw(10) << val << " ";
            }
            break;
        }
        case 3:
            continuar = false;
            break;
        default:
            std::cout << "Opción inválida.\n";
            break;
        }
    }
    
}
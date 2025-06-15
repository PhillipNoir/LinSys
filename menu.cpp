/**
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
 */
#include "Matrix.h"
#include "Methods.h"
#include <iostream>
#include <iomanip>
#include "menu.h"

void menuPrincipal(){
    int opcion {0};
    bool continuar {true};

    std::cout<<"¡Bienvenido al resolvedor de sistemas de ecuaciones lineales!\n";
    
    int size{0};
    bool mostrarPasos{true};

    while (continuar)
    {
        std::cout<<"\nPor favor, elija el método por el cual deseas resolver tu sistema de ecuaciones lineales o selecciona la opción 'Salir' para terminar el programa: \n";
        std::cout << "1. Método de Gauss\n";
        std::cout << "2. Método de Gauss-Jordan\n";
        std::cout << "3. Salir\n";
        std::cout << "Su elección: ";
        std::cin >> opcion;

        switch (opcion)
        {
        case 1: {
            std::cout<<"Ingrese el tamaño del sistema: ";
            std::cin>>size;
            Matrix A(size, size);
            Matrix b (size, 1);
            std::cout << "Ingrese la matriz A:\n";
            A.fillMatrix();
            std::cout << "Ingrese el vector b:\n";
            b.fillMatrix();
            std::cout<<"¿Desea ver los pasos de la solución? (Y:1/N:0): \n";
            std::cin>>mostrarPasos;
            std::vector<double> solution = gaussElimination(A, b, mostrarPasos);
            std::cout << "Solución:\n";
    
            for (double val : solution) {
                std::cout << std::setw(10) << val << " ";
            }
            break;
        }
        case 2: {
            std::cout<<"Ingrese el tamaño del sistema: ";
            std::cin>>size;
            Matrix A(size, size);
            Matrix b (size, 1);
            std::cout << "Ingrese la matriz A:\n";
            A.fillMatrix();
            std::cout << "Ingrese el vector b:\n";
            b.fillMatrix();
            std::cout<<"¿Desea ver los pasos de la solución? (Y:1/N:0): \n";
            std::cin>>mostrarPasos;
            std::vector<double> solution = gaussJordanElimination(A, b, mostrarPasos);
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
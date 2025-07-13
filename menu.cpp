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
        std::cout << "\nPor favor, elija el método por el cual deseas resolver tu sistema de ecuaciones lineales o selecciona la opción 'Salir' para terminar el programa: \n";
        std::cout << "1. Método de Gauss\n";
        std::cout << "2. Método de Gauss-Jordan\n";
        std::cout << "3. Método de Jacobi\n";
        std::cout << "4. Método de Gauss-Seidel\n";
        std::cout << "5. Salir\n";
        std::cout << "\nNotas:\n";
        std::cout << "- Los métodos de Gauss y Gauss-Jordan son generalmente más rápidos para sistemas pequeños y medianos.\n";
        std::cout << "- El método de Jacobi es más adecuado para sistemas grandes y puede ser más lento, pero es más robusto en términos de convergencia.\n";
        std::cout << "- El método de Gauss-Seidel es una mejora del método de Jacobi y puede converger más rápido en algunos casos, pero también requiere que la matriz sea diagonal dominante.\n";
        std::cout << "- Si el sistema es grande, se recomienda usar Jacobi o Gauss-Seidel para evitar problemas de memoria.\n";
        std::cout << "- Los métodos de Gauss y Gauss-Jordan pueden ser menos adecuados para equipos de bajos recursos con sistemas muy grandes debido a su mayor consumo de memoria.\n";
        opcion = leerEntero("Su elección: ");
        std::cout << "Entrada registrada como " << opcion << " (cualquier parte decimal fue ignorada en caso de haber sido ingresada).\n";

        switch (opcion)
        {
        case 1: {
            size = leerEntero("Ingrese el tamaño de la matriz: ");
            std::cout << "Entrada registrada como " << size << " (cualquier parte decimal fue ignorada en caso de haber sido ingresada).\n";
            Matrix A(size, size);
            Matrix b (size, 1);
            std::cout << "Ingrese la matriz A:\n";
            A.fillMatrix();
            std::cout << "Ingrese el vector b:\n";
            b.fillMatrix();
            mostrarPasos = leerBooleano("¿Desea ver los pasos de la solución? (Y:1/N:0)\n");
            std::vector<double> solution = gaussElimination(A, b, mostrarPasos);
            advertenciaSistemaGrande(size);
            std::cout << "Solución:\n";
    
            for (double val : solution) {
                std::cout << std::setw(10) << val << " ";
            }
            break;
        }
        case 2: {
            size = leerEntero("Ingrese el tamaño de la matriz: ");
            std::cout << "Entrada registrada como " << size << " (cualquier parte decimal fue ignorada en caso de haber sido ingresada).\n";
            Matrix A(size, size);
            Matrix b (size, 1);
            std::cout << "Ingrese la matriz A:\n";
            A.fillMatrix();
            std::cout << "Ingrese el vector b:\n";
            b.fillMatrix();
            mostrarPasos = leerBooleano("¿Desea ver los pasos de la solución? (Y:1/N:0)\n");
            std::vector<double> solution = gaussJordanElimination(A, b, mostrarPasos);
            advertenciaSistemaGrande(size);
            std::cout << "Solución:\n";
    
            for (double val : solution) {
                std::cout << std::setw(10) << val << " ";
            }
            break;
        }
        case 3: {
            // Para el método de Jacobi, no se requiere mostrar pasos intermedios
            size = leerEntero("Ingrese el tamaño de la matriz: ");
            std::cout << "Entrada registrada como " << size << " (cualquier parte decimal fue ignorada en caso de haber sido ingresada).\n";
            Matrix A(size, size);
            Matrix b (size, 1);
            std::cout << "Ingrese la matriz A:\n";
            A.fillMatrix();
            std::cout << "Ingrese el vector b:\n";
            b.fillMatrix();
            std::vector<double> solution = jacobiMethod(A, b, 1e-6, 500);
            std::cout << "Solución:\n";
            for (double val : solution) {
                std::cout << std::setw(10) << val << " ";
            }
            break;
        }
        case 4: {
            // Para el método de Gauss-Seidel, no se requiere mostrar pasos intermedios
            size = leerEntero("Ingrese el tamaño de la matriz: ");
            std::cout << "Entrada registrada como " << size << " (cualquier parte decimal fue ignorada en caso de haber sido ingresada).\n";
            Matrix A(size, size);
            Matrix b (size, 1);
            std::cout << "Ingrese la matriz A:\n";
            A.fillMatrix();
            std::cout << "Ingrese el vector b:\n";
            b.fillMatrix();
            std::vector<double> solution = gaussSeidelMethod(A, b, 1e-6, 500);
            std::cout << "Solución:\n";
            for (double val : solution) {
                std::cout << std::setw(10) << val << " ";
            }
            break;
        }
        case 5: 
            continuar = false;
            std::cout << "Gracias por usar el programa. ¡Hasta luego!\n";
            break;
        default:
            std::cout << "Opción inválida.\n";
            break;
        }
    }
    
}
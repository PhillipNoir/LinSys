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
 */
#ifdef _WIN32
#include<windows.h>
#endif
#include "Matrix.hpp"
#include "Methods.hpp"
#include <iostream>
#include <iomanip>
#include "menu.hpp"

/**
 * @brief Función principal del programa.
 * 
 *  Llama a la función `menuPrincipal()` que gestiona la interacción
 *  con el usuario para resolver sistemas de ecuaciones lineales mediante
 *  los métodos de Gauss y Gauss-Jordan.
 * 
 * @return int Código de salida del programa (0 si finaliza correctamente).
 */
int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif
    menuPrincipal();
    return 0;
}

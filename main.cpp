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
 * @version [0.4.0]
 */
#include "Matrix.h"
#include "Methods.h"
#include <iostream>
#include <iomanip>
#include "menu.h"

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
    menuPrincipal();
    return 0;
}

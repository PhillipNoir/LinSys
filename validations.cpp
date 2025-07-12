/*@file validations.cpp
 * @brief Funciones de validación y lectura de entradas del usuario.
 * Este archivo contiene funciones para validar entradas del usuario y leer valores enteros, decimales y boolean
*/

#include "Matrix.hpp"
#include "Methods.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include "menu.hpp"
#include <limits>

/**
 * @brief Muestra una advertencia si el sistema es demasiado grande.
 * 
 * Esta función imprime un mensaje de advertencia si el tamaño del sistema es mayor a 10,
 * sugiriendo que se mostrarán solo los resultados finales para evitar sobrecargar la consola.
 * 
 * @param size Tamaño del sistema de ecuaciones.
 */
void advertenciaSistemaGrande(int size){
    bool mostrarPasos = size<11;
    if (mostrarPasos == false)
    {
        std::cout << "Aviso: El sistema tiene muchas ecuaciones. Para evitar sobrecargar la consola, solo se mostrará la solución final.\n";
    }
    
}

/**
 * @brief Lee un número entero desde la entrada estándar.
 * 
 * Esta función solicita al usuario que ingrese un número entero y valida la entrada.
 * Si la entrada no es válida, solicita al usuario que vuelva a intentarlo.
 * 
 * @param mensaje Mensaje que se muestra al usuario para solicitar la entrada.
 * @return int El número entero ingresado por el usuario.
 */
int leerEntero(const std::string& mensaje) {
    int valor;
    while (true) {
        std::cout << mensaje;
        std::cin >> valor;

        if (std::cin.fail()) {
            std::cin.clear(); // Limpia el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descarta la entrada incorrecta
            std::cout << "Entrada inválida. Por favor ingresa un número entero.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descarta cualquier resto
            return valor;
        }
    }
}

/**
 * @brief Lee un número decimal desde la entrada estándar.
 * 
 * Esta función solicita al usuario que ingrese un número decimal y valida la entrada.
 * Si la entrada no es válida, solicita al usuario que vuelva a intentarlo.
 * 
 * @param mensaje Mensaje que se muestra al usuario para solicitar la entrada.
 * @return double El número decimal ingresado por el usuario.
 */
double leerDecimal(const std::string& mensaje) {
    double valor;
    while (true) {
        std::cout << mensaje;
        std::cin >> valor;

        if (std::cin.fail()) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada inválida. Por favor ingresa un número.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valor;
        }
    }
}

/**
 * @brief Lee un valor booleano desde la entrada estándar.
 * 
 * Esta función solicita al usuario que ingrese un valor booleano (1 para verdadero, 0 para falso)
 * y valida la entrada. Si la entrada no es válida, solicita al usuario que vuelva a intentarlo.
 * 
 * @param mensaje Mensaje que se muestra al usuario para solicitar la entrada.
 * @return bool El valor booleano ingresado por el usuario.
 */
bool leerBooleano(const std::string& mensaje) {
    int entrada;
    while (true) {
        std::cout << mensaje;
        std::cin >> entrada;

        if (std::cin.fail() || (entrada != 0 && entrada != 1)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada inválida. Ingresa 1 para Sí o 0 para No.\n";
        } else {
            return entrada;
        }
    }
}

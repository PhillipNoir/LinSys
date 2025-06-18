#include "Matrix.hpp"
#include "Methods.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include "menu.hpp"
#include <limits>

void advertenciaSistemaGrande(int size){
    bool mostrarPasos = size<11;
    if (mostrarPasos == false)
    {
        std::cout << "Aviso: El sistema tiene muchas ecuaciones. Para evitar sobrecargar la consola, solo se mostrará la solución final.\n";
    }
    
}

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

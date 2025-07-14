/**
 * @file String.cpp
 * @brief Implementación de la clase String para manejo de cadenas dinámicas.
 * 
 * Esta clase proporciona métodos para crear, manipular y convertir números a cadenas,
 * utilizando punteros inteligentes para gestión segura de memoria.
 */
#include "String.hpp"
#include <iostream>
#include <stdexcept>

/**
 * @brief Constructor por defecto - crea cadena vacía.
 */
String::String() : length(0) {
    data = std::make_unique<char[]>(1);
    data[0] = '\0';
}

/**
 * @brief Constructor desde cadena literal C.
 */
String::String(const char* str) {
    if (str == nullptr) {
        length = 0;
        data = std::make_unique<char[]>(1);
        data[0] = '\0';
        return;
    }
    
    // Calcular longitud manualmente (sin strlen)
    length = 0;
    while (str[length] != '\0') {
        length++;
    }
    
    data = std::make_unique<char[]>(length + 1);
    for (int i = 0; i < length; i++) {
        data[i] = str[i];
    }
    data[length] = '\0';
}

/**
 * @brief Constructor con tamaño específico.
 */
String::String(int size) : length(size) {
    data = std::make_unique<char[]>(size + 1);
    for (int i = 0; i <= size; i++) {
        data[i] = '\0';
    }
}

int String::getLength() const {
    return length;
}

char& String::at(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Índice fuera de rango");
    }
    return data[index];
}

const char& String::at(int index) const {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Índice fuera de rango");
    }
    return data[index];
}

/**
 * @brief Convierte entero a cadena manualmente.
 */
void String::fromInt(int value) {
    bool isNegative = value < 0;
    if (isNegative) value = -value;
    
    // Contar dígitos
    int temp = value;
    int digits = (temp == 0) ? 1 : 0;
    while (temp > 0) {
        digits++;
        temp /= 10;
    }
    
    length = digits + (isNegative ? 1 : 0);
    data = std::make_unique<char[]>(length + 1);
    
    // Llenar desde atrás
    int index = length - 1;
    do {
        data[index--] = '0' + (value % 10);
        value /= 10;
    } while (value > 0);
    
    if (isNegative) {
        data[0] = '-';
    }
    
    data[length] = '\0';
}

/**
 * @brief Convierte float a cadena manualmente.
 */
void String::fromFloat(float value, int precision) {
    fromDouble(static_cast<double>(value), precision);
}

/**
 * @brief Convierte double a cadena manualmente.
 */
void String::fromDouble(double value, int precision) {
    bool isNegative = value < 0.0;
    if (isNegative) value = -value;
    
    // Separar parte entera y decimal
    long long intPart = static_cast<long long>(value);
    double fracPart = value - intPart;
    
    // Convertir parte entera
    String intStr;
    intStr.fromInt(static_cast<int>(intPart));
    
    // Calcular tamaño total necesario
    int totalSize = intStr.getLength() + 1 + precision; // entero + punto + decimales
    if (isNegative) totalSize++;
    
    length = totalSize;
    data = std::make_unique<char[]>(length + 1);
    
    // Copiar signo si es negativo
    int pos = 0;
    if (isNegative) {
        data[pos++] = '-';
    }
    
    // Copiar parte entera (sin signo)
    int startInt = isNegative ? 1 : 0;
    for (int i = startInt; i < intStr.getLength(); i++) {
        data[pos++] = intStr.at(i);
    }
    
    // Agregar punto decimal
    data[pos++] = '.';
    
    // Convertir parte decimal
    for (int i = 0; i < precision; i++) {
        fracPart *= 10;
        int digit = static_cast<int>(fracPart);
        data[pos++] = '0' + digit;
        fracPart -= digit;
    }
    
    data[length] = '\0';
}

void String::assign(const char* str) {
    if (str == nullptr) {
        clear();
        return;
    }
    
    // Calcular nueva longitud
    int newLength = 0;
    while (str[newLength] != '\0') {
        newLength++;
    }
    
    length = newLength;
    data = std::make_unique<char[]>(length + 1);
    
    for (int i = 0; i < length; i++) {
        data[i] = str[i];
    }
    data[length] = '\0';
}

const char* String::c_str() const {
    return data.get();
}

void String::print() const {
    std::cout << data.get();
}

void String::clear() {
    length = 0;
    data = std::make_unique<char[]>(1);
    data[0] = '\0';
}

// Agrega estas implementaciones al final del archivo, antes del último }

/**
 * @brief Constructor de copia.
 */
String::String(const String& other) {
    length = other.length;
    data = std::make_unique<char[]>(length + 1);
    
    for (int i = 0; i < length; i++) {
        data[i] = other.data[i];
    }
    data[length] = '\0';
}

/**
 * @brief Operador de asignación por copia.
 */
String& String::operator=(const String& other) {
    if (this != &other) {  // Evitar auto-asignación
        length = other.length;
        data = std::make_unique<char[]>(length + 1);
        
        for (int i = 0; i < length; i++) {
            data[i] = other.data[i];
        }
        data[length] = '\0';
    }
    return *this;
}

/**
 * @brief Concatena con otra cadena String.
 */
String String::operator+(const String& other) const {
    int newLength = length + other.length;
    String result(newLength);
    
    // Copiar esta cadena
    for (int i = 0; i < length; i++) {
        result.data[i] = data[i];
    }
    
    // Copiar la otra cadena
    for (int i = 0; i < other.length; i++) {
        result.data[length + i] = other.data[i];
    }
    
    result.data[newLength] = '\0';
    result.length = newLength;
    
    return result;
}

/**
 * @brief Concatena con cadena literal C.
 */
String String::operator+(const char* str) const {
    if (str == nullptr) {
        return *this;  // Retorna copia de esta cadena
    }
    
    // Calcular longitud de str manualmente
    int strLength = 0;
    while (str[strLength] != '\0') {
        strLength++;
    }
    
    int newLength = length + strLength;
    String result(newLength);
    
    // Copiar esta cadena
    for (int i = 0; i < length; i++) {
        result.data[i] = data[i];
    }
    
    // Copiar la cadena literal
    for (int i = 0; i < strLength; i++) {
        result.data[length + i] = str[i];
    }
    
    result.data[newLength] = '\0';
    result.length = newLength;
    
    return result;
}
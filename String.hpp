/**
 * @file String.hpp
 * @brief Declaración de la clase String para manejo de cadenas de caracteres dinámicas.
 * 
 * Proporciona una estructura de datos para cadenas con gestión automática de memoria
 * mediante punteros inteligentes y métodos para conversión de números a texto.
 */
#ifndef STRING_HPP
#define STRING_HPP

#include <memory>

/**
 * @class String
 * @brief Clase que representa una cadena de caracteres dinámica.
 *
 * Esta clase permite crear cadenas de tamaño variable, acceder y modificar caracteres,
 * y convertir números (int, float, double) a representación de texto.
 * Utiliza punteros inteligentes (`std::unique_ptr`) para gestionar la memoria de forma segura.
 */
class String {
private:
    int length;
    std::unique_ptr<char[]> data; // Almacén de caracteres con puntero inteligente
    
public:
    /**
     * @brief Constructor por defecto - crea cadena vacía.
     */
    String();
    
    /**
     * @brief Constructor que crea cadena desde literal C.
     * @param str Cadena literal de C.
     */
    String(const char* str);
    
    /**
     * @brief Constructor que crea cadena de tamaño específico.
     * @param size Tamaño inicial de la cadena.
     */
    String(int size);
    
    /**
     * @brief Devuelve la longitud de la cadena.
     * @return Longitud actual de la cadena.
     */
    int getLength() const;
    
    /**
     * @brief Acceso seguro a un carácter con verificación de límites.
     * @param index Índice del carácter (0 <= index < length).
     * @return char& Referencia al carácter solicitado.
     * @throws std::out_of_range Si el índice está fuera de rango.
     */
    char& at(int index);
    
    /**
     * @brief Acceso seguro a un carácter (versión const).
     * @param index Índice del carácter.
     * @return const char& Referencia constante al carácter.
     */
    const char& at(int index) const;
    
    /**
     * @brief Convierte un entero a cadena de caracteres.
     * @param value Valor entero a convertir.
     */
    void fromInt(int value);
    
    /**
     * @brief Convierte un float a cadena de caracteres.
     * @param value Valor float a convertir.
     * @param precision Número de decimales (por defecto 2).
     */
    void fromFloat(float value, int precision = 2);
    
    /**
     * @brief Convierte un double a cadena de caracteres.
     * @param value Valor double a convertir.
     * @param precision Número de decimales (por defecto 6).
     */
    void fromDouble(double value, int precision = 6);
    
    /**
     * @brief Asigna una cadena literal C a esta cadena.
     * @param str Cadena literal a asignar.
     */
    void assign(const char* str);
    
    /**
     * @brief Obtiene puntero a los datos internos (para compatibilidad con C).
     * @return const char* Puntero a los datos internos.
     */
    const char* c_str() const;
    
    /**
     * @brief Imprime la cadena en consola.
     */
    void print() const;
    
    /**
     * @brief Limpia la cadena (la deja vacía).
     */
    void clear();

    // Agrega estas líneas después de los métodos existentes, antes del }; final

/**
 * @brief Concatena esta cadena con otra cadena String.
 * @param other Otra cadena String a concatenar.
 * @return String Nueva cadena resultado de la concatenación.
 */
String operator+(const String& other) const;

/**
 * @brief Concatena esta cadena con una cadena literal C.
 * @param str Cadena literal C a concatenar.
 * @return String Nueva cadena resultado de la concatenación.
 */
String operator+(const char* str) const;

/**
 * @brief Operador de asignación por copia.
 * @param other Otra cadena String a copiar.
 * @return String& Referencia a esta cadena.
 */
String& operator=(const String& other);

/**
 * @brief Constructor de copia.
 * @param other Otra cadena String a copiar.
 */
String(const String& other);
};



#endif
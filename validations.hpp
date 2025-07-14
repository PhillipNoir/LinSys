/**
 * @file validations.cpp
 * @brief Implenmentación de diferentes validaciones para mejorar la robustez y estabilidad del programa.
 * 
 * Este archivo contiene la declaración de 3 funciones quue evitan que el usuario ingrese entradas incorrectas para el tipo de dato 
 * esperado y una para lanzar una advertencia en caso de que el usuario ingrese un sistema cuya magnitud comprometa la estabilidad
 * del sistema si se muestran los pasos.
 */
#ifndef VALIDATIONS_HPP
#define VALIDATIONS_HPP

#include "validations.hpp"
#include "String.hpp"

/**
 * @brief Muestra una advertencia si el sistema de ecuaciones es muy grande.
 *
 * Si el número de ecuaciones es mayor o igual a 11, se recomienda al usuario no mostrar pasos
 * para evitar sobrecargar la salida en consola.
 *
 * @param size Número de ecuaciones del sistema.
 */
void advertenciaSistemaGrande(int size);

/**
 * @brief Solicita y valida la entrada de un número entero desde consola.
 *
 * La función seguirá solicitando al usuario hasta que se ingrese un valor entero válido.
 *
 * @param mensaje Mensaje que se muestra al usuario para solicitar la entrada.
 * @return Un número entero ingresado correctamente.
 */
int leerEntero(const String& mensaje);

/**
 * @brief Solicita y valida la entrada de un número decimal (double) desde consola.
 *
 * La función seguirá solicitando al usuario hasta que se ingrese un valor decimal válido.
 *
 * @param mensaje Mensaje que se muestra al usuario para solicitar la entrada.
 * @return Un número decimal ingresado correctamente.
 */
double leerDecimal(const String& mensaje);

/**
 * @brief Solicita al usuario una entrada booleana (1 o 0) y la valida.
 *
 * Esta función valida que el usuario ingrese 1 (true) o 0 (false). Repite la solicitud hasta obtener una entrada válida.
 *
 * @param mensaje Mensaje que se muestra al usuario para solicitar la entrada.
 * @return true si el usuario ingresa 1, false si ingresa 0.
 */
bool leerBooleano(const String& mensaje);

#endif
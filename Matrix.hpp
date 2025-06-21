/**
 * @file Matrix.hpp
 * @brief Declaración de la clase Matrix para representar y manipular matrices dinámicas.
 * 
 * Proporciona una estructura de datos para matrices con gestión automática de memoria
 * mediante punteros inteligentes y métodos para acceso seguro, llenado e impresión.
 *
 */
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>

/**
 * @class Matrix
 * @brief Clase que representa una matriz dinámica de tamaño variable.
 *
 * Esta clase permite crear matrices de tamaño definido en tiempo de ejecución, acceder y
 * modificar sus valores mediante el método 'at', y realizar operaciones básicas, como
 * impresion y llenado manual.
 * Utiliza punteros inteligentes (`std::unique_ptr`) para gestionar la memoria de forma segura.
 */
class Matrix {
    private:
        int rows;
        int cols;
        std::unique_ptr<std::unique_ptr<double[]>[]> matriz; // Almacén de datos en una matriz de punteros inteligentes. //
    public:
        /**
        * @brief Constructor de la matriz.
        *
        * Asigna dinamicamente la memoria para una matriz de tamaño `rows` x `cols`.
        *
         * @param r Número de filas.
        * @param c Número de columnas.
        */
        Matrix(int r, int c);

        /**
        * @brief Devuelve el número de filas de la matriz.
        * @return Número de filas
        */
        int getRows() const;

        /**
        * @brief Devuelve el número de columnas de la matriz.
        * @return Número de columnas
        */
        int getCols() const;

        /**
        * @brief Acceso seguro a un elemento de la matriz con verificación de límites.
        *
        * Devuelve una referencia al elemento en la posición indicada.
        * Lanza `std::out_of_range` si los índices exceden los límites.
        *
        * @param row Índice de fila (0 <= row < rows).
        * @param col Índice de columna (0 <= col < cols).
        * @return double& Referencia al elemento solicitado.
        *
        * @throws std::out_of_range Si los índices están fuera de rango.
        */
        double& at(int row, int col);

        /**
         * @brief Llena la matriz con valores ingresados por el usuario desde la consola.
        *
        * Solicita al usuario cada elemento de la matriz, indicando su posición.
        */
        void fillMatrix();
    
        /**
        * @brief Imprime la matriz en la consola con un formato tabulado.
        *
        * Utiliza `std::setw` para alinear columnas y mostrar la matriz de manera legible.
        */
        void print() const;
};

#endif

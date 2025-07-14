# Changelog

Todas las modificaciones significativas de este proyecto serán documentadas en este archivo.

El formato está basado en [Keep a Changelog](https://keepachangelog.com/es/1.0.0/).

## [1.2.2] - 2025- 07-14
## Refactorizado
- Eliminación de std::string en todos los métodos numéricos y otros archivos que lo utilicen.
- Implementación de una clase String para dejar de depender de otro componente de la STL.
- Todos los archivos que antes usaban std::string ahora usan objetos de la clase String, asegurando compatibilidad con sistemas donde la STL está limitada.
- Se refactoriza función del método Jacobi y del Metodo Gauss-Seidel para que ambos dependan de una función auxiliar que aplica un método iterativo dependiendo del parámetro booleano ingresado.
- README.md actualizado y traducido al inglés.

## [1.2.1] - 2025-07-13
## Refactorizado
- Eliminación de std::vector en todos los métodos numéricos para la solución de sistemas de ecuaciones lineales.
- Todos los métodos (gaussElimination, Gauss-Jordan, Jacobi y Gauss-Seidel) ahora utilizan exclusivamente la clase Matrix para representar y devolver soluciones, asegurando compatibilidad con sistemas donde la STL está limitada.
- Los métodos iterativos ahora lanzan una excepción si no convergen, garantizando un comportamiento consistente y seguro.
- El código es ahora más portable, facil de mantener y extender, y permite un control total sobre la representación y manipulación de matrices.
- Proximamente se eliminará std::string para una mayor compatibilidad y portabilidad sin necesidad de la STL.

## [1.2.0] - 2025-07-12
## Actualizado
- README.md actualizado con el nuevo método.
- Se implementa el método de Gauss-Seidel como alternativa para sistemas grandes y equipos de bajos recursos.
- Actualización de la documentación para incluir el nuevo método.

## [1.1.0] - 2025-07-12
## Actualizado
- Se agrega documentación Doxygen a validations.cpp.
- README.md actualizado con el nuevo método.
- Se implementa el método de Jacobi como alternativa para sistemas grandes y equipos de bajos recursos.
- Actualización de la documentación para incluir el nuevo método.

## [1.0.0] - 2025-06-20
## Actualizado
- Se agrega documentación Doxygen al proyecto en HTML y PDF.
- Se actualiza el README.md con el logo del proyecto y logo del desarrollador.
- Se mejora ligeramente la interfaz.
- Se actualiza documentación y se agrega documentación Doxygen a utils.cpp, utils.hpp, validations.cpp y validations.hpp.

## [0.7.0] - 2025-06-20
## Actualizado
- Se mejora la presentación de la interfaz y se resuelven los errores de compatibilidad con letras españolas en windows.

## [0.6.2] - 2025-06-19
## Mejorado
- Se crea un validations.cpp y un validations.cpp para validar evitar entradas de usuario incorrectas.
- Se refactorizan funciones en utils.cpp y methods.cpp para evitar errores numéricos, manejar casos de infinitas soluciones y reportes de mal condicionamiento.

## [0.6.0] - 2025-06-16
## Actualizado
- Se crea un utils.cpp y un utils.hpp para las funciones que se separaron de Methods.cpp
- Se refactorizan múltiples funciones para mayor modularidad.
- Se cambia la extensión de los .h a .hpp para C++ moderno puro.
- README actualizado

## [0.5.0] - 2025-06-18
### Añadido
- Se implementa Matrix como class para orientación a objetos y se realizan los cambios en los métodos correspondientes para el correcto funcionamiento.
- README actualizado.

## [0.4.7] - 2025-06-15
### Actualizado y añadido
- Se elimina el versionado en la documentación del código y se deja únicamente el del repositorio ara evitar conflictos.
- Changelog añadido.

## [0.4.6] - 2025-06-15
### Actualizado
- El repositorio local es subido al repositorio de github.

## [0.4.5] - 2025-06-15
### Actualizado
- Readme actualizado.

## [0.4.4] - 2025-06-15
### Actualizado
- Licencia actualizada.

## [0.4.3] - 2025-06-15
### Comenzado
- Repositorio de GitHub creado.

## [0.4.2] - 2025-06-15
### Actualizado
- Documentación Doxygen actualizada.

## [0.4.1] - 2025-06-15
### Arreglado
- Se arregla un error al incluir un header que impedía la compilación.

## [0.4.0] - 2025-06-15
### Añadido
- Se añade el menu principal.
- Se limpia la función main

## [0.3.0] - 2025-06-15
### Añadido
- Se añade solución paso por paso.
- Función para imprimir la matriz de forma aumentada.

## [0.2.0] - 2025-06-12
### Añadido
- Método de Gauss-Jordan implementado

## [0.1.0] - 2025-06-12
### Añadido
- Método de Gauss implementado
- Documentación en Doxygen añadida

## [0.0.1] - 2025-06-05
### Comenzado
- Proyecto creado.

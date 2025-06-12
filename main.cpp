#include "Matrix.h"
#include "Methods.h"
#include <iostream>

int main() {
    int n;
    std::cout << "Bienvenido, ingrese el tamaño del sistema: ";
    std::cin >> n;

    Matrix A(n, n);
    Matrix b(n, 1);

    std::cout << "Ingrese la matriz A:\n";
    A.fillMatrix();

    std::cout << "Ingrese el vector b:\n";
    b.fillMatrix();


    std::vector<double> x = gaussElimination(A, b);

    std::cout << "Solución:\n";
    for (double val : x) {
        std::cout << val << ",";
    }
    
    return 0;
}

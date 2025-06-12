#include "Methods.h"
#include "Matrix.h"
#include <vector>
#include <stdexcept>
#include <cmath>

std::vector<double> gaussElimination(Matrix& A, Matrix& b) {
    int n = A.rows;

    // Eliminación hacia adelante
    for (int k = 0; k < n; ++k) {
        // 1. Encontrar fila con el mayor valor absoluto en la columna k
        int maxRow = k;
        for (int i = k + 1; i < n; ++i) {
            if (std::abs(A.at(i, k)) > std::abs(A.at(maxRow, k))) {
                maxRow = i;
            }
        }

        // 2. Intercambiar filas en A y b si es necesario
        if (A.at(maxRow, k) == 0) {
            throw std::runtime_error("El sistema no tiene solución única.");
        }

        if (maxRow != k) {
            for (int j = 0; j < n; ++j) {
                std::swap(A.at(k, j), A.at(maxRow, j));
            }
            std::swap(b.at(k, 0), b.at(maxRow, 0));
        }

        // 3. Eliminar hacia abajo
        for (int i = k + 1; i < n; ++i) {
            double factor = A.at(i, k) / A.at(k, k);
            for (int j = k; j < n; ++j) {
                A.at(i, j) -= factor * A.at(k, j);
            }
            b.at(i, 0) -= factor * b.at(k, 0);
        }
    }

    // Sustitución regresiva
    std::vector<double> x(n);
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0.0;
        for (int j = i + 1; j < n; ++j) {
            sum += A.at(i, j) * x[j];
        }
        x[i] = (b.at(i, 0) - sum) / A.at(i, i);
    }

    return x;

}

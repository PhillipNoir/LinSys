#ifndef UTILS_HPP
#define UTILS_HPP

#include "Matrix.hpp"

void forwardElimination(Matrix& A, Matrix& b, bool mostrarPasos);
void backwardElimination(Matrix& A, Matrix& b, bool mostrarPasos);
#endif
#ifndef METHODS_H
#define METHODS_H

#include "Matrix.h"
#include <vector>

std::vector<double> gaussElimination(Matrix& A, Matrix& b);
std::vector<double> gaussJordanElimination(Matrix& A, Matrix& b);


#endif

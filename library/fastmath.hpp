#ifndef FASTMATH_H
#define FASTMATH_H

#include <cstddef> // Para usar size_t
#include <cstdlib> // Para malloc e free

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct Matrix {
    int row;
    int col;
    double** n;
};

EXPORT void Matrix_alloc(Matrix *mat);
EXPORT void Matrix_free(Matrix *mat);
EXPORT Matrix* multiplyMatrices(Matrix* a, Matrix* b);

#ifdef __cplusplus
}
#endif

#endif // FASTMATH_H

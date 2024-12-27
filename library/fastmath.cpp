#include "fastmath.hpp"
#include <cmath>

EXPORT double compute_heavy(double x) {
    return sin(x) * cos(x) + sqrt(x);
}

//typedef struct Matrix {
//    int row;
//    int col;
//    double **n;
//} Matrix;

void alloc_matrix_double(double ***mat, size_t row, size_t col) {
    *mat = (double **)malloc(sizeof(double *) * row);
    for (size_t i = 0; i < row; ++i) {
        (*mat)[i] = (double *)malloc(sizeof(double) * col);
    }
}

void free_matrix_double(double ***mat, size_t row) {
    for (size_t i = 0; i < row; ++i) {
        free((*mat)[i]);
    }
    free((*mat));
}

EXPORT void Matrix_alloc(Matrix *mat) {
    alloc_matrix_double(&mat->n, mat->row, mat->col);
}

EXPORT void Matrix_free(Matrix *mat) {
    free_matrix_double(&mat->n, mat->row);
}

EXPORT Matrix* multiplyMatrices(Matrix* a, Matrix* b) {
    if ((a->col != a->row) && ((a->row != b->row))) {
        return nullptr;
    }

    Matrix* result = new Matrix;
    result->col = a->col;
    result->row = a->row;
    Matrix_alloc(result);

    // Multiplicação de matrizes
    for (size_t i = 0; i < a->row; ++i) {
        for (size_t j = 0; j < b->col; ++j) {
            result->n[i][j] = 0;
            for (size_t k = 0; k < a->col; ++k) {
                result->n[i][j] += a->n[i][k] * b->n[k][j];
            }
        }
    }

    return result;
}
#include "hw1.h"
#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <type_traits> // std::is_intergral and std::is_floating_point
#include <sstream> // ostringstream

/** implement a Linear Algebra library for c++.*/
namespace algebra {

template <typename T>
Matrix<T> zeros(size_t n, size_t m) {
    return Matrix<T>(n, std::vector<T>(m, 0));
}

template <typename T>
Matrix<T> ones(size_t n, size_t m) {
    return Matrix<T>(n, std::vector<T>(m, 1));
}

template <typename T>
Matrix<T> random(size_t n, size_t m, T min, T max) {
    // Hardware Random
    static std::random_device rd;
    static std::mt19937 gen(rd());

    // use contexpr Optimizion code
    if constexpr (std::is_integral_v<T>) { // type integral 
        std::uniform_int_distribution<T> dist(min, max);
        return Matrix<T>(n, std::vector<T>(m, dist(gen)));
    } else if constexpr (std::is_floating_point_v<T>) { // type float
        std::uniform_real_distribution<T> dist(min, max);
        return Matrix<T>(n, std::vector<T>(m, dist));
    } else {
        static_assert(std::is_arithmetic_v<T>, "Type Error!!!");
    }
}

template <typename T>
void show(const Matrix<T>& matrix) {
    std::ostringstream oss; // ostringstream
    for (auto& row : matrix) {
        for (auto& elem : row) {
            std::cout << std::fixed << std::setprecision(3) << elem << " ";
        }
        oss << '\n';
    }
    std::cout << oss.str();
}

template <typename T>
Matrix<T> multiply(const Matrix<T>& matrix, T c) {
    // copy with matrix -> result
    auto result = matrix;

    for (auto& row : matrix) {
        std::transform(row.begin(), row.end(), row.begin(),
            [c](T value){ // value with in row[element...];
                c * value;
        });
    }
    return result;
}

// matrix1 -> row, matrix2 -> col euqals mul_matrix(row, col)
template <typename T>
Matrix<T> multiply(const Matrix<T>& matrix1, const Matrix<T>& matrix2) {
    // O^3
    size_t m = matrix1.size(); // row
    size_t n = matrix1[0].size(); // row
    size_t p = matrix2[0].size(); // row
    Matrix<T> result(m, (std::vector<T>(p, 0)));

    for (size_t i = 0; i < m; i += 1) {
        for (size_t k = 0; k < n; k += 1) {
            for (size_t j = 0; j < p; j += 1) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

template <typename T>
Matrix<T> sum(const Matrix<T>& matrix, T c) {
    // Simple to multipy(const Matrix<T>& matrix, T c)
    auto result = matrix;

    for (auto& row : matrix) {
        std::transform(row.begin(), row.end(), row.begin(),
            [c](T value){
                c + value;
        });
    }
    return result;
}

template <typename T>
Matrix<T> sum(const Matrix<T>& matrix1, const Matrix<T>& matrix2) {
    size_t m = matrix1.size();
    size_t p = matrix2[0].size();
    Matrix<T> result(m, (std::vector<T>(p, 0)));

    for (size_t i = 0; i < m; i += 1) {
        for (size_t j = 0; j < p; j += 1) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    return result;
}

template <typename T>
Matrix<T> transpose(const Matrix<T>& matrix) {
    auto result = matrix;

    for (size_t i = 0; i < matrix.size(); i += 1) {
        for (size_t j = 0; j < matrix[0].size(); j += 1) {
            result[i][j] = matrix[j][i];
        }
    }

    return result;
}

template <typename T>
Matrix<T> minor(const Matrix<T>& matrix, size_t n, size_t m) {
    return Matrix<T>__;
}

template <typename T>
T determinant(const Matrix<T>& matrix) {
    return Matrix<T>__;
}

template <typename T>
Matrix<T> inverse(const Matrix<T>& matrix) {
    return Matrix<T>__;
}

template <typename T>
Matrix<T> concatenate(const Matrix<T>& matrix1, const Matrix<T>& matrix2, int axis) {
    return Matrix<T>__;
}

template <typename T>
Matrix<T> ero_swap(const Matrix<T>& matrix, size_t r1, size_t r2) {
    return Matrix<T>__;
}

template <typename T>
Matrix<T> ero_multiply(const Matrix<T>& matrix, size_t r, T c) {
    return Matrix<T>__;
}

template <typename T>
Matrix<T> ero_sum(const Matrix<T>& matrix, size_t r1, T c, size_t r2) {
    return Matrix<T>__;
}

template <typename T>
Matrix<T> upper_triangular(const Matrix<T>& matrix) {
    return Matrix<T>__;
}

}
#ifndef AP_HW1_H
#define AP_HW1_H

#include <vector>

// use template
template <typename T>
using Matrix = std::vector<std::vector<T>>;

/** Define Linear Algebra library for c++ */
namespace algebra {

// Create a n x m matrix with all elements equal to zero.
template <typename T>
Matrix<T> zeros(size_t n, size_t m);

// Create a n x m matrix with all elements equal to one.
template <typename T>
Matrix<T> ones(size_t n, size_t m);

/** Create a n x m matrix with all elements a random number between min and max.
 * to generate a random number you are not allowed to use rand and srand functions. 
 * instead, use the <random> library first introduced in c++11.
 */
template <typename T>
Matrix<T> random(size_t n, size_t m, T min, T max);

/** Show implement this function so 
 * that it will display the matrix in a beautiful way. 
 * To display your matrices use the <iomanip> library. 
 * when showing the numbers, each element of the matrix 
 * should have exactly 3 decimal places. 
 */
template <typename T>
void show(const Matrix<T>& matrix);

// ultiplies the matrix into the constant scalar c.
template <typename T>
Matrix<T> multiply(const Matrix<T>& matrix, T c);

// Multiplies the matrix1 into matrix2. (this is not an element-wise multiplication)
template <typename T>
Matrix<T> multiply(const Matrix<T>& matrix1, const Matrix<T>& matrix2);

// Adds the constant number c to every element of matrix.
template <typename T>
Matrix<T> sum(const Matrix<T>& matrix, T c);

// Adds 2 matrices to each other.
template <typename T>
Matrix<T> sum(const Matrix<T>& matrix1, const Matrix<T>& matrix2);

// Will generate the transpose matrix of the input matrix.
template <typename T>
Matrix<T> transpose(const Matrix<T>& matrix);

/** Create the minor of the input matrix with respect to nth 
 * row and mth column. Note. the indices in c++ start from 0 not 1
 */
template <typename T>
Matrix<T> minor(const Matrix<T>& matrix, size_t n, size_t m);

// Calculates the determinant of the input matrix.
template <typename T>
T determinant(const Matrix<T>& matrix);

// generates the matrix's inverse.
template <typename T>
Matrix<T> inverse(const Matrix<T>& matrix);

/** concatenate matrix1 and matrix2 along the specified axis.
 * (axis=0: on top of each other | axis=1: alongside each other).
 */
template <typename T>
Matrix<T> concatenate(const Matrix<T>& matrix1, const Matrix<T>& matrix2, int axis=0);


/** 1. swapping two rows. 
 *  2. multiplying a row into a constant number.
 *  3. multiplying a row into a constant number and add it to another row.
 */

// swap swaps r1th row with r2th.
template <typename T>
Matrix<T> ero_swap(const Matrix<T>& matrix, size_t r1, size_t r2);

// multiply multiplies every element in rth row with constant number c.
template <typename T>
Matrix<T> ero_multiply(const Matrix<T>& matrix, size_t r, T c);

// sum adds   r1th x c   into r2th row.
template <typename T>
Matrix<T> ero_sum(const Matrix<T>& matrix, size_t r1, T c, size_t r2);

/** upper triangular implement this function so that it will 
 * calculate the upper triangular form of the matrix using the ERO operations.
 */
template <typename T>
Matrix<T> upper_triangular(const Matrix<T>& matrix);

}

#endif //AP_HW1_H
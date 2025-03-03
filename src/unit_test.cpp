
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "hw1.h"

TEST(HW1Test, ZEROS) {
    Matrix<double> matrix{algebra::zeros<double>(5, 6)};

    // check the size of the matrix
    EXPECT_EQ(matrix.size(), 5);
    EXPECT_EQ(matrix[0].size(), 6);

    // check the value of the elements
    for (const auto& row : matrix)
        for (const auto& elem : row)
            EXPECT_DOUBLE_EQ(elem, 0);
}

TEST(HW1Test, ONES) {
    Matrix<double> matrix{algebra::ones<double>(7, 3)};

    // check the size of the matrix
    EXPECT_EQ(matrix.size(), 7);
    EXPECT_EQ(matrix[0].size(), 3);

    // check the value of the elements
    for (const auto& row : matrix)
        for (const auto& elem : row)
            EXPECT_DOUBLE_EQ(elem, 1);
}

TEST(HW1Test, RANDOM1) {
    using ::testing::AllOf;
    using ::testing::Ge;
    using ::testing::Lt;

    Matrix<double> matrix{algebra::random<double>(4, 4, -5, 7)};

    // check the size of the matrix
    EXPECT_EQ(matrix.size(), 4);
    EXPECT_EQ(matrix[0].size(), 4);

    // check the value of the elements
    for (const auto& row : matrix)
        for (const auto& elem : row)
            EXPECT_THAT(elem, AllOf(Ge(-5.0), Lt(7)));

    // show the matrix to test algebra::show function
    std::cout << "random matrix [-5, 7)" << std::endl;
    algebra::show<double>(matrix);
    std::cout << std::endl;
}

TEST(HW1Test, RANDOM2) {
    // Caution: min cannot be greater than max
    EXPECT_THROW(algebra::random<double>(3, 4, 4, 2), std::logic_error);
}

TEST(HW1Test, MULTIPLY1) {
    Matrix<double> matrix{algebra::random<double>(3, 4, -4, 2)};
    Matrix<double> mult{algebra::multiply<double>(matrix, 3.5)};

    // check the size of the matrix
    EXPECT_EQ(mult.size(), 3);
    EXPECT_EQ(mult[0].size(), 4);

    // check the value of the elements
    for (size_t i{}; i < mult.size(); i++)
        for (size_t j{}; j < mult[i].size(); j++)
            EXPECT_NEAR(mult[i][j], matrix[i][j]*3.5, 0.03);
}

TEST(HW1Test, MULTIPLY2) {
    // Caution: multiplication of 2 empty matrix
    Matrix<double> matrix{algebra::multiply<double>(Matrix<double>{}, Matrix<double>{})};
    EXPECT_TRUE(matrix.empty());

    // Caution: matrices with wrong dimensions cannot be multiplied
    EXPECT_THROW(algebra::multiply<double>(Matrix<double>{{1, 2, 3}, {4, 5, 6}}, Matrix<double>{{1, 2, 3}, {4, 5, 6}}), std::logic_error);
}

TEST(HW1Test, MULTIPLY3) {
    Matrix<double> matrix1{{-3, 3, 1.7}, {4, -4, 2.6}, {-5, 5, 3.5}};
    Matrix<double> matrix2{{2.5}, {-2}, {-5.5}};
    Matrix<double> matrix{algebra::multiply<double>(matrix1, matrix2)};

    // check the size of the matrix
    EXPECT_EQ(matrix.size(), 3);
    EXPECT_EQ(matrix[0].size(), 1);

    // check the value of the elements
    EXPECT_NEAR(matrix[0][0], -22.85, 0.03);
    EXPECT_NEAR(matrix[1][0], 3.7, 0.03);
    EXPECT_NEAR(matrix[2][0], -41.75, 0.03);
}

TEST(HW1Test, MULTIPLY4) {
    Matrix<double> matrix1{{-3, 2, 1.7}, {4, -5, 2.6}, {7.2, 5, 3.5}};
    Matrix<double> matrix2{{6.5}, {-2}, {-5}};
    Matrix<double> matrix{algebra::multiply<double>(matrix1, matrix2)};

    // check the size of the matrix
    EXPECT_EQ(matrix.size(), 3);
    EXPECT_EQ(matrix[0].size(), 1);

    // check the value of the elements
    EXPECT_NEAR(matrix[0][0], -32, 0.03);
    EXPECT_NEAR(matrix[1][0], 23, 0.03);
    EXPECT_NEAR(matrix[2][0], 19.3, 0.03);
}

TEST(HW1Test, SUM1) {
    // Caution: sum of an empty matrix
    EXPECT_TRUE(algebra::sum<double>(Matrix<double>{}, 1.5).empty());

    Matrix<double> matrix{algebra::random<double>(2, 5, 0, 4)};
    Matrix<double> sum{algebra::sum<double>(matrix, 2.44)};

    // check the size of the matrix
    EXPECT_EQ(sum.size(), 2);
    EXPECT_EQ(sum[0].size(), 5);

    // check the value of the elements
    for (size_t i{}; i < sum.size(); i++)
        for (size_t j{}; j < sum[i].size(); j++)
            EXPECT_NEAR(sum[i][j], matrix[i][j]+2.44, 0.03);
}

TEST(HW1Test, SUM2) {
    // Caution: sum of 2 empty matrices
    EXPECT_TRUE(algebra::sum<double>(Matrix<double>{}, Matrix<double>{}).empty());

    // Caution: matrices with wrong dimensions cannot be summed
    EXPECT_THROW(algebra::sum<double>(Matrix<double>{{1, 2, 3}}, Matrix<double>{}), std::logic_error);

    Matrix<double> matrix1{algebra::random<double>(3, 2, -1, 4)};
    Matrix<double> matrix2{algebra::random<double>(3, 2, -8, -3)};
    Matrix<double> sum{algebra::sum<double>(matrix1, matrix2)};

    // check the size of the matrix
    EXPECT_EQ(sum.size(), 3);
    EXPECT_EQ(sum[0].size(), 2);

    // check the value of the elements
    for (size_t i{}; i < sum.size(); i++)
        for (size_t j{}; j < sum[i].size(); j++)
            EXPECT_NEAR(sum[i][j], matrix1[i][j]+matrix2[i][j], 0.03);
}

TEST(HW1Test, TRANSPOSE) {
    // Caution: transpose of an empty matrix is an empty matrix
    EXPECT_TRUE(algebra::transpose<double>(Matrix<double>{}).empty());

    Matrix<double> matrix{algebra::random<double>(3, 5, -2, 5)};
    Matrix<double> transpose = algebra::transpose<double>(matrix);

    // check the size of the matrix
    EXPECT_EQ(transpose.size(), 5);
    EXPECT_EQ(transpose[0].size(), 3);

    // check the value of the elements
    for (size_t i{}; i < transpose.size(); i++)
        for (size_t j{}; j < transpose[i].size(); j++)
            EXPECT_DOUBLE_EQ(transpose[i][j], matrix[j][i]);
}

TEST(HW1Test, MINOR1) {
    Matrix<double> matrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<double> minor = algebra::minor<double>(matrix, 1, 2);

    // Check the size of the matrix
    EXPECT_EQ(minor.size(), 2);
    EXPECT_EQ(minor[0].size(), 2);

    // Check the value of the elements
    EXPECT_DOUBLE_EQ(minor[0][0], matrix[0][0]);
    EXPECT_DOUBLE_EQ(minor[0][1], matrix[0][1]);
    EXPECT_DOUBLE_EQ(minor[1][0], matrix[2][0]);
    EXPECT_DOUBLE_EQ(minor[1][1], matrix[2][1]);
}

TEST(HW1Test, MINOR2) {
    Matrix<double> matrix{{7, 2.5, 3.1}, {4.2, 5, 10.4}, {70.7, 8, 0}};
    Matrix<double> minor = algebra::minor<double>(matrix, 1, 1);

    // Check the size of the matrix
    EXPECT_EQ(minor.size(), 2);
    EXPECT_EQ(minor[0].size(), 2);

    // Check the value of the elements
    EXPECT_DOUBLE_EQ(minor[0][0], matrix[0][0]);
    EXPECT_DOUBLE_EQ(minor[0][1], matrix[0][2]);
    EXPECT_DOUBLE_EQ(minor[1][0], matrix[2][0]);
    EXPECT_DOUBLE_EQ(minor[1][1], matrix[2][2]);
}

TEST(HW1Test, DETERMINANT1) {
    // Caution: determinant of an empty matrix
    EXPECT_EQ(algebra::determinant<double>(Matrix<double>{}), 1);

    // Caution: non-square matrices have no determinant
    EXPECT_THROW(algebra::determinant<double>(Matrix<double>{{1, 2, 3}, {4, 5, 6}}), std::logic_error);

    // Test case
    Matrix<double> matrix{{-1, 1.5, -1.75, -2}, {-2, 2.5, -2.75, -3}, {3, 3.5, -3.75, -4}, {4, 4.5, 4.75, -5}};
    EXPECT_NEAR(algebra::determinant<double>(matrix), -28.5, 0.03);
}

TEST(HW1Test, DETERMINANT2) {
    // Test case
    Matrix<double> matrix{{1, 1.5, -1.75, 2}, {2, 2.5, -2.75, 3}, {3, 3.5, -3.75, 4}, {4, 4.5, 4.75, 5}};
    EXPECT_DOUBLE_EQ(algebra::determinant<double>(matrix), 0);
}

TEST(HW1Test, INVERSE1) {
    // Caution: inverse of an empty matrix
    EXPECT_TRUE(algebra::inverse<double>(Matrix<double>{}).empty());

    // Caution: non-square matrices have no inverse
    EXPECT_THROW(algebra::inverse<double>(Matrix<double>{{1, 2, 3}, {40, 5, -6}}), std::logic_error);

    // Caution: singular matrices have no inverse
    Matrix<double> non_singular_matrix{{1, 1.5, -1.75, 2}, {2, 2.5, -2.75, 3}, {3, 3.5, -3.75, 4}, {4, 4.5, 4.75, 5}};
    EXPECT_THROW(algebra::inverse<double>(non_singular_matrix), std::logic_error);

    // Test case
    Matrix<double> matrix{{-1, 1.5, -1.75, -2}, {-2, 2.5, -2.75, -3}, {3, 3.5, -3.75, -4}, {4, 4.5, 4.75, -5}};
    Matrix<double> inverse{algebra::inverse<double>(matrix)};
    EXPECT_NEAR(inverse[0][0], 0.16, 0.03);
    EXPECT_NEAR(inverse[1][1], 3.31, 0.03);
    EXPECT_NEAR(inverse[3][1], 2.67, 0.03);
    EXPECT_NEAR(inverse[0][3], 0, 0.03);
}


TEST(HW1Test, INVERSE2) {
    // Test case
    Matrix<double> matrix{{-12, 1.5, -1.75, -2}, {-2, 2.5, -2.75, -3}, {25, 3.5, -3.75, -4}, {4, 4.5, 4.75, -51}};
    Matrix<double> inverse{algebra::inverse<double>(matrix)};
    EXPECT_NEAR(inverse[0][0], 0.05, 0.03);
    EXPECT_NEAR(inverse[1][1], 18.07, 0.03);
    EXPECT_NEAR(inverse[3][1], 2.80, 0.03);
    EXPECT_NEAR(inverse[0][3], 0, 0.03);
}

TEST(HW1Test, CONCATENATE1) {
    // Caution: matrices with wrong dimensions cannot be concatenated
    EXPECT_THROW(algebra::concatenate<double>(Matrix<double>{{1, 2}}, Matrix<double>{{1, 2, 3}, {4, 5, 6}}, 0), std::logic_error);

    // Test case
    Matrix<double> matrix1{algebra::random<double>(2, 3, 0, 1)};
    Matrix<double> matrix2{algebra::random<double>(4, 3, 0, 1)};
    Matrix<double> matrix{algebra::concatenate<double>(matrix1, matrix2, 0)};

    // Check the size of the matrix
    EXPECT_EQ(matrix.size(), 6);
    EXPECT_EQ(matrix[0].size(), 3);

    // Check the value of the elements
    EXPECT_DOUBLE_EQ(matrix[0][0], matrix1[0][0]);
    EXPECT_DOUBLE_EQ(matrix[1][2], matrix1[1][2]);
    EXPECT_DOUBLE_EQ(matrix[2][0], matrix2[0][0]);
    EXPECT_DOUBLE_EQ(matrix[5][2], matrix2[3][2]);
}

TEST(HW1Test, CONCATENATE2) {
    // Caution: matrices with wrong dimensions cannot be concatenated
    EXPECT_THROW(algebra::concatenate<double>(Matrix<double>{{1, 2}}, Matrix<double>{{1, 2, 3}, {4, 5, 6}}, 1), std::logic_error);

    // Test case
    Matrix<double> matrix1{algebra::random<double>(2, 3, 0, 1)};
    Matrix<double> matrix2{algebra::random<double>(2, 1, 0, 1)};
    Matrix<double> matrix{algebra::concatenate<double>(matrix1, matrix2, 1)};

    // Check the size of the matrix
    EXPECT_EQ(matrix.size(), 2);
    EXPECT_EQ(matrix[0].size(), 4);

    // Check the value of the elements
    EXPECT_DOUBLE_EQ(matrix[0][0], matrix1[0][0]);
    EXPECT_DOUBLE_EQ(matrix[1][2], matrix1[1][2]);
    EXPECT_DOUBLE_EQ(matrix[0][3], matrix2[0][0]);
    EXPECT_DOUBLE_EQ(matrix[1][3], matrix2[1][0]);
}

TEST(HW1Test, ERO_SWAP) {
    // Caution: r1 or r2 inputs are out of range
    EXPECT_THROW(algebra::ero_swap<double>(Matrix<double>{{1, 2}}, 0, 1), std::logic_error);

    // Test case
    Matrix<double> matrix{algebra::random<double>(4, 3, 0, 4)};
    Matrix<double> swap{algebra::ero_swap<double>(matrix, 2, 3)};

    // Check the swap
    EXPECT_TRUE(swap[0] == matrix[0]);
    EXPECT_TRUE(swap[1] == matrix[1]);
    EXPECT_TRUE(swap[2] == matrix[3]);
    EXPECT_TRUE(swap[3] == matrix[2]);
}

TEST(HW1Test, ERO_MULTIPLY) {
    Matrix<double> matrix{algebra::random<double>(4, 3, 0, 4)};
    Matrix<double> ero{algebra::ero_multiply<double>(matrix, 2, 1.5)};

    EXPECT_TRUE(ero[0] == matrix[0]);
    EXPECT_TRUE(ero[1] == matrix[1]);
    EXPECT_TRUE(ero[3] == matrix[3]);

    // Check the value of the elements
    for (size_t i{}; i < ero[2].size(); i++)
        EXPECT_NEAR(ero[2][i], matrix[2][i]*1.5, 0.03);
}

TEST(HW1Test, ERO_SUM) {
    Matrix<double> matrix{algebra::random<double>(4, 3, 0, 4)};
    Matrix<double> ero{algebra::ero_sum<double>(matrix, 0, 2, 3)};

    EXPECT_TRUE(ero[0] == matrix[0]);
    EXPECT_TRUE(ero[1] == matrix[1]);
    EXPECT_TRUE(ero[2] == matrix[2]);

    // Check the value of the elements
    for (size_t i{}; i < ero[3].size(); i++)
        EXPECT_NEAR(ero[3][i], matrix[0][i]*2 + matrix[3][i], 0.03);
}

TEST(HW1Test, UPPER_TRIANGULAR1) {
    // Caution: empty matrix
    EXPECT_TRUE(algebra::upper_triangular<double>(Matrix<double>{}).empty());

    // Caution: non-square matrices have no upper triangular form
    EXPECT_THROW(algebra::upper_triangular<double>(Matrix<double>{{1, 2, 3}, {4, 5, 6}}), std::logic_error);

    // Test case 1
    Matrix<double> matrix1{{1, 2}, {5, 7}};
    Matrix<double> res1{algebra::upper_triangular<double>(matrix1)};
    EXPECT_NEAR(res1[0][0], 1, 0.03);
    EXPECT_NEAR(res1[1][0], 0, 0.03);
    EXPECT_NEAR(res1[1][1], -3, 0.03);

    // Test case 2
    Matrix<double> matrix2{{1, 2, 3}, {4, 7, 5}, {6, 1, 3}};
    Matrix<double> res2{algebra::upper_triangular<double>(matrix2)};
    EXPECT_NEAR(res2[0][0], 1, 0.03);
    EXPECT_NEAR(res2[1][0], 0, 0.03);
    EXPECT_NEAR(res2[2][0], 0, 0.03);
    EXPECT_NEAR(res2[2][1], 0, 0.03);
    EXPECT_NEAR(res2[2][2], 62, 0.03);
}

TEST(HW1Test, BONUS) {
    // Test case
    Matrix<double> matrix2{{0, 2, 3}, {4, 7, 5}, {6, 1, 3}};
    Matrix<double> res2{algebra::upper_triangular<double>(matrix2)};
    EXPECT_NEAR(res2[0][0], 4, 0.03);
    EXPECT_NEAR(res2[1][0], 0, 0.03);
    EXPECT_NEAR(res2[2][0], 0, 0.03);
    EXPECT_NEAR(res2[2][1], 0, 0.03);
    EXPECT_NEAR(res2[2][2], 39/4.0, 0.03);
}

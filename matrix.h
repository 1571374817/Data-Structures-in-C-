//
// Created by 15713 on 24-10-24.
//

#ifndef MATRIX_H
#define MATRIX_H
#include <ranges>
#include <bits/ranges_base.h>
#include <bits/range_access.h>

// 本文件采用行主次序实现矩阵的描述
// 用一位数组element存储

template<typename T>
class matrix {
public:
    matrix(int rows = 0, int columns = 0);

    matrix(const matrix<T> &other_matrix);

    ~matrix() { delete[] element; };

    int rows() const { return rows; };
    int columns() const { return columns; };

    T &operator()(int row, int column);

    matrix<T> &operator=(const matrix<T> &other_matrix);

    matrix<T> operator+() const;

    matrix<T> operator+(const matrix<T> &other_matrix) const;

    matrix<T> operator-() const;

    matrix<T> operator-(const matrix<T> &other_matrix) const;

    matrix<T> operator*(const matrix<T> &other_matrix) const;

    matrix<T> &operator+=(const matrix<T> &other_matrix);

private:
    int rows;
    int columns;
    T *element;
};
#endif //MATRIX_H

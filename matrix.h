//
// Created by 15713 on 24-10-24.
//

#ifndef MATRIX_H
#define MATRIX_H

#include <algorithm>
#include <iostream>

// 本文件采用行主次序实现矩阵的描述
// 用一位数组element存储

template<typename T>
class matrix {
public:
    // 构造函数、拷贝构造函数、析构函数
    explicit matrix(int rows = 0, int columns = 0);

    matrix(const matrix<T> &other_matrix);

    ~matrix() { delete[] element; };

    [[nodiscard]] int get_rows() const { return rows; }; // 返回矩阵的行数

    [[nodiscard]] int get_columns() const { return columns; }; // 返回矩阵的列数

    T &operator()(int row, int column);

    matrix<T> &operator=(const matrix<T> &other_matrix);

    matrix<T> operator+(const matrix<T> &other_matrix) const;

    matrix<T> operator-(const matrix<T> &other_matrix) const;

    matrix<T> operator*(const matrix<T> &other_matrix) const;

    matrix<T> &operator+=(const matrix<T> &other_matrix);

    void output() const;

private:
    int rows;    // 矩阵的行数
    int columns; // 矩阵的列数
    T *element;  // 一维数组存储矩阵
};

// 构造函数
template<typename T>
matrix<T>::matrix(int rows, int columns) {
    // 检验参数有效性
    if(rows < 0 || columns < 0) {
        throw std::invalid_argument("rows and columns must be >= 0");
    }
    // 可以生成 0 × 0 矩阵，但是不能生成 n × 0 或者 0 × n 的矩阵
    if((rows == 0 || columns == 0) && (rows != columns)) {
        throw std::invalid_argument("either both or neither rows and columns should be 0");
    }
    // 创建矩阵
    this->rows = rows;
    this->columns = columns;
    element = new T[rows*columns]();
}

// 拷贝构造函数
template<typename T>
matrix<T>::matrix(const matrix<T> &other_matrix) {
    rows = other_matrix.rows;
    columns = other_matrix.columns;
    element = new T[rows*columns];
    // 复制元素
    std::copy(other_matrix.element, other_matrix.element + rows * columns, element);
}

// 重载操作符 =
template<typename T>
matrix<T> &matrix<T>::operator=(const matrix<T> &other_matrix) {
    // 检测自我复制
    if(this != &other_matrix) {
        delete[] element;
        rows = other_matrix.rows;
        columns = other_matrix.columns;
        element = new T[rows*columns];
        std::copy(other_matrix.element, other_matrix.element + rows * columns, element);
    }
    return *this;
}

// ()表示矩阵索引，重载函数操作符(),接受两个整形参数
// 返回引用，可以用来取值，也可以用来赋值
// 对矩阵的索引从(1,1)开始，即row >= 1,column >= 1
template<typename T>
T &matrix<T>::operator()(int row, int column) {
    // 检测参数是否合法
    if(row < 1 || row > rows || column < 1 || column > columns) {
        throw std::invalid_argument("either row or column must be in the range [1, %d]");
    }
    return element[(row - 1) * columns + column - 1];
}

// 重载操作符 + ,实现矩阵加法
template<typename T>
matrix<T> matrix<T>::operator+(const matrix<T> &other_matrix) const {
    if(rows != other_matrix.rows || columns != other_matrix.columns) {
        throw std::invalid_argument("Matrix dimensions must match for addition.");
    }
    matrix<T> result(rows, columns);
    for(int i = 0; i < rows * columns; ++i) {
        result.element[i] = this->element[i] + other_matrix.element[i];
    }
    return result;
}

// 重载操作符-,实现矩阵减法
template<typename T>
matrix<T> matrix<T>::operator-(const matrix<T> &other_matrix) const {
    if(rows != other_matrix.rows || columns != other_matrix.columns) {
        throw std::invalid_argument("Number of rows and columns must be equal");
    }
    matrix<T> result(rows, columns);
    for(int i = 0; i < rows * columns; ++i) {
        result.element[i] = this->element[i] - other_matrix.element[i];
    }
    return result;
}

// 重载操作符*,实现矩阵乘法
template<typename T>
matrix<T> matrix<T>::operator*(const matrix<T> &other_matrix) const {
        if(columns != other_matrix.rows) {
            throw std::invalid_argument("Matrix dimensions do not match for multiplication");
        }
        matrix<T> result(rows, other_matrix.columns);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other_matrix.columns; ++j) {
                T sum = 0;
                for (int k = 0; k < columns; ++k) {
                    sum += element[i * columns + k] * other_matrix.element[k * other_matrix.columns + j];
                }
                result.element[i * other_matrix.columns + j] = sum;
            }
        }
        return result;
}

template<typename T>
matrix<T> &matrix<T>::operator+=(const matrix<T> &other_matrix) {
    if(rows != other_matrix.rows || columns != other_matrix.columns) {
        throw std::invalid_argument("Number of rows and columns must be equal");
    }
    for(int i = 0; i < rows * columns; ++i) {
        this->element[i] = this->element[i] + other_matrix.element[i];
    }
    return *this;
}

template<typename T>
void matrix<T>::output() const {
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            std::cout << element[i * columns + j] << " ";
        }
        std::cout << '\n'; // 输出每行后换行
    }
}
#endif //MATRIX_H

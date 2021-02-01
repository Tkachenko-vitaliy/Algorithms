#pragma once

#include <vector>

/*
This is a naive implementation of matrix.
The implementation is very childish. 
It has to be implementated as contiguous array where position of the item is calculated from row and col.
However, the implementation is very convenient for debug: I can explicitly see the content for every row and column.
*/

template<typename T>
class Matrix
{
public:
    Matrix(size_t rows, size_t cols);
    Matrix(const Matrix& m);
    Matrix(Matrix&& m);

    void resize(size_t rows, size_t columns);
    void set(size_t row, size_t col, const T& item);
    void fill(const T& item);
    T get(size_t row, size_t col);
    const T get(size_t row, size_t col) const;
    size_t rows() const;
    size_t cols() const;

    std::vector<T>& operator[] (size_t row);
    const std::vector<T>& operator[] (size_t row) const;
    Matrix<T>& operator = (const Matrix<T>& matrix);
    Matrix<T>& operator = (Matrix<T>&& matrix);
    Matrix<T> operator* (const Matrix<T>& m);
private:
    std::vector<std::vector<T>> data;
};

template<typename T>
void Matrix<T>::resize(size_t rows, size_t columns)
{
    data.resize(rows);
    for (std::vector<T>& rowVector : data )
    {
        rowVector.resize(columns);
    }
}


template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols)
{
    if (rows != 0 && cols != 0)
    {
        resize(rows, cols);
    }
}

template<typename T>
Matrix<T>::Matrix(const Matrix& m)
{
    *this = m;
}

template<typename T>
Matrix<T>::Matrix(Matrix&& m)
{
    *this = m;
}

template<typename T>
void Matrix<T>::set(size_t row, size_t col, const T& item)
{
    data[row][col] = item;
}

template<typename T>
void Matrix<T>::fill(const T& item)
{
    for (auto& row : data)
    {
        for (auto& col : row)
        {
            col = item;
        }
    }
}

template<typename T>
T Matrix<T>::get(size_t row, size_t col)
{
    return data[row][col];
}

template<typename T>
size_t Matrix<T>::rows() const
{
    return data.size();
}

template<typename T>
size_t Matrix<T>::cols() const
{
    if (data.size() != 0)
    {
        return data[0].size();
    }
    else
    {
        return 0;
    }
}

template<typename T>
std::vector<T>& Matrix<T>::operator[] (size_t row)
{ 
    return data[row];
}

template<typename T>
const std::vector<T>& Matrix<T>::operator[] (size_t row) const
{
    return data[row];
}

template<typename T>
Matrix<T>& Matrix<T>::operator = (const Matrix<T>& matrix)
{
    data = matrix.data;
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator = (Matrix<T>&& matrix)
{
    data = std::move(matrix.data);
    return *this;
}


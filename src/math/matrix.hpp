#pragma once

#include <vector>
#include "vec.hpp"

using namespace std;

class MatrixProxy
{
private:
    vector<double> &_data;
    unsigned int _row;
    unsigned int _columnLength;

public:
    MatrixProxy(vector<double> &data, unsigned int row, unsigned int columnLength);

    double &operator[](unsigned int column);
};

class Matrix
{
private:
    vector<double> _data;
    unsigned int _rowLength;
    unsigned int _columnLength;

public:
    Matrix(const vector<double> &data, unsigned int rowLength, unsigned int columnLength);

    Matrix(const Vec2 &vec);

    Matrix(const Vec3 &vec);

    Matrix(const VecHomogenous &vec);

    Matrix(const Matrix &matrix);

    MatrixProxy operator[](unsigned int row);

    double Get(unsigned int row, unsigned int column) const;

    unsigned int GetRowLength() const;

    unsigned int GetColumnLength() const;

    double Determinant() const;

    Matrix Minor(unsigned int row, unsigned int column) const;

    Matrix Cofactor() const;

    Matrix Adjoint() const;

    Matrix Transpose() const;

    Matrix Inverse() const;

    Matrix operator*(const Matrix &vec) const;

    Matrix operator*(const double &fact) const;

    unique_ptr<Vec> ToVec() const;

    unique_ptr<Vec> operator*(const Vec2 &vec) const;

    unique_ptr<Vec> operator*(const Vec3 &vec) const;

    unique_ptr<Vec> operator*(const VecHomogenous &vec) const;

    void Print() const;
};

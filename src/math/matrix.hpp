#pragma once

#include <vector>
#include "vec.hpp"

using namespace std;

class MatrixProxy
{
private:
    std::vector<double> &_row;

public:
    MatrixProxy(std::vector<double> &row);

    double operator[](unsigned int column);
};

class Matrix
{
private:
    vector<vector<double>> _data;
    unsigned int _rowLength;
    unsigned int _columnLength;

public:
    Matrix(vector<double> data, unsigned int rowLength, unsigned int columnLength);

    Matrix(const Vec2 &vec);

    Matrix(const Vec3 &vec);

    Matrix(const VecHomogenous &vec);

    MatrixProxy operator[](unsigned int row);

    double Get(unsigned int row, unsigned int column) const;

    unsigned int GetRowLength() const;

    unsigned int GetColumnLength() const;

    double Determinant() const;

    Matrix Minor(unsigned int row, unsigned int column) const;

    Matrix Comatrix() const;

    Matrix Transpose() const;

    Matrix operator*(const Matrix &vec) const;

    Vec2 operator*(const Vec2 &vec) const;

    Vec3 operator*(const Vec3 &vec) const;

    VecHomogenous operator*(const VecHomogenous &vec) const;
};

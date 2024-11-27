#pragma once

#include <vector>

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
    unsigned int _row;
    unsigned int _column;

public:
    Matrix(vector<double> data, unsigned int row, unsigned int column);

    MatrixProxy operator[](unsigned int row);
};

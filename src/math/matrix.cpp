#include "matrix.hpp"
#include <stdexcept>

MatrixProxy::MatrixProxy(std::vector<double> &row) : _row(row) {};

double MatrixProxy::operator[](unsigned int column)
{
    return _row[column];
};

Matrix::Matrix(vector<double> data, unsigned int row, unsigned int column) : _row(row), _column(column)
{
    if (data.size() != _row * _column)
    {
        throw invalid_argument("matrix invalid row column regarding datd size");
    }
    for (unsigned int i = 0; i < _row; i++)
    {
        vector<double> temp;
        for (unsigned int j = 0; j < _column; j++)
        {
            temp.push_back(data[(i * _column) + j]);
        }
        _data.push_back(temp);
    }
};

MatrixProxy Matrix::operator[](unsigned int row)
{
    return MatrixProxy(_data[row]);
}
#include "matrix.hpp"
#include <stdexcept>
#include <cmath>

MatrixProxy::MatrixProxy(std::vector<double> &row) : _row(row) {};

double MatrixProxy::operator[](unsigned int column)
{
    return _row[column];
};

Matrix::Matrix(vector<double> data, unsigned int rowLength, unsigned int columnLength) : _rowLength(rowLength), _columnLength(columnLength)
{
    if (data.size() != _rowLength * _columnLength)
    {
        throw invalid_argument("matrix invalid row and column regarding data size");
    }
    for (unsigned int i = 0; i < _rowLength; i++)
    {
        vector<double> temp;
        for (unsigned int j = 0; j < _columnLength; j++)
        {
            temp.push_back(data[(i * _columnLength) + j]);
        }
        _data.push_back(temp);
    }
};

Matrix::Matrix(const Vec2 &vec) : _rowLength(2), _columnLength(1)
{
    _data.push_back({vec.x});
    _data.push_back({vec.y});
};

Matrix::Matrix(const Vec3 &vec) : _rowLength(3), _columnLength(1)
{
    _data.push_back({vec.x});
    _data.push_back({vec.y});
    _data.push_back({vec.z});
};

Matrix::Matrix(const VecHomogenous &vec) : _rowLength(4), _columnLength(1)
{
    _data.push_back({vec.x});
    _data.push_back({vec.y});
    _data.push_back({vec.z});
    _data.push_back({vec.w});
};

MatrixProxy Matrix::operator[](unsigned int row)
{
    return MatrixProxy(_data[row]);
}

double Matrix::Get(unsigned int row, unsigned int column) const
{
    return this->_data[row][column];
};

unsigned int Matrix::GetRowLength() const
{
    return this->_rowLength;
};

unsigned int Matrix::GetColumnLength() const
{
    return this->_columnLength;
};

Matrix Matrix::operator*(const Matrix &other) const
{
    const unsigned int length = this->GetColumnLength();
    if (length != other.GetRowLength())
    {
        throw invalid_argument("impossible to mathematically operate * on those matrixes");
    }
    vector<double> res;
    for (unsigned int thisRow = 0; thisRow < this->GetRowLength(); thisRow++)
    {
        for (unsigned int otherColumn = 0; otherColumn < other.GetColumnLength(); otherColumn++)
        {
            double sum = 0;
            for (unsigned int i = 0; i < length; i++)
            {
                sum += this->Get(thisRow, i) * other.Get(i, otherColumn);
            }
            res.push_back(sum);
        }
    }
    return Matrix(res, this->GetRowLength(), other.GetColumnLength());
};

Vec2 Matrix::operator*(const Vec2 &vec) const
{
    Matrix res = (*this) * Matrix(vec);
    return Vec2(res[0][0], res[1][0]);
};

Vec3 Matrix::operator*(const Vec3 &vec) const
{
    Matrix res = (*this) * Matrix(vec);
    return Vec3(res[0][0], res[1][0], res[2][0]);
};

VecHomogenous Matrix::operator*(const VecHomogenous &vec) const
{
    Matrix res = (*this) * Matrix(vec);
    return VecHomogenous(res[0][0], res[1][0], res[2][0], res[3][0]);
};

double Matrix::Determinant() const
{
    unsigned int size = this->GetColumnLength();
    if (size != this->GetRowLength())
    {
        throw invalid_argument("impossible to mathematically calculate determinant on unsquare matrixes");
    }
    if (size == 1)
    {
        return this->Get(0, 0);
    }
    if (size == 2)
    {
        return (this->Get(0, 0) * this->Get(1, 1)) - (this->Get(0, 1) * this->Get(1, 0));
    }
    double determinant = 0;
    for (unsigned int i = 0; i < size; i++)
    {
        int sign = pow(-1, i);
        double cofactor = sign * this->Get(0, i);
        Matrix minor = this->Minor(0, i);
        determinant += cofactor * minor.Determinant();
    }
    return determinant;
}

Matrix Matrix::Minor(unsigned int row, unsigned int column) const
{
    vector<double> data;
    for (unsigned int itRow = 0; itRow < this->GetRowLength(); itRow++)
    {
        if (itRow == row)
        {
            continue;
        }
        for (unsigned int itColumn = 0; itColumn < this->GetColumnLength(); itColumn++)
        {
            if (itColumn == column)
            {
                continue;
            }
            data.push_back(this->Get(itRow, itColumn));
        }
    }
    return Matrix(data, this->GetRowLength() - 1, this->GetColumnLength() - 1);
}

Matrix Matrix::Comatrix() const
{
    vector<double> data;
    for (unsigned int itRow = 0; itRow < this->GetRowLength(); itRow++)
    {
        for (unsigned int itColumn = 0; itColumn < this->GetColumnLength(); itColumn++)
        {
            int sign = pow(-1, (itRow * this->GetRowLength()) + itColumn);
            Matrix minor = this->Minor(itRow, itColumn);
            double determinant = minor.Determinant();
            data.push_back(sign * determinant);
        }
    }
    return Matrix(data, this->GetRowLength(), this->GetColumnLength());
}

Matrix Matrix::Transpose() const
{
    vector<double> data;
    for (unsigned int itColumn = 0; itColumn < this->GetColumnLength(); itColumn++)
    {
        for (unsigned int itRow = 0; itRow < this->GetRowLength(); itRow++)
        {
            data.push_back(this->Get(itRow, itColumn));
        }
    }
    return Matrix(data, this->GetColumnLength(), this->GetRowLength());
}
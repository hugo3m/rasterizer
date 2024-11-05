#include "rgba.hpp"
#include <algorithm>

RGBA::RGBA(int r, int g, int b, int a) : _r(max(0, min(255, r))), _g(max(0, min(255, g))), _b(max(0, min(255, b))), _a(max(0, min(255, a)))
{
}

array<int, 4> RGBA::Unpack() const
{
    return {
        max(0, min(255, this->_r)), max(0, min(255, this->_g)), max(0, min(255, this->_b)), max(0, min(255, this->_a))};
}

RGBA RGBA::operator*(double const &other) const
{
    return RGBA(this->_r * other, this->_g * other, this->_b * other, this->_a);
}
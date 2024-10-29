#include "rgba.hpp"
#include <algorithm>

RGBA::RGBA(int r, int g, int b, int a) : _r(r), _g(g), _b(b), _a(a)
{
}

array<int, 4> RGBA::Unpack() const
{
    return {
        max(0, min(255, this->_r)), max(0, min(255, this->_g)), max(0, min(255, this->_b)), max(0, min(255, this->_a))};
}
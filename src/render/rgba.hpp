#pragma once

#include <array>

using namespace std;

class RGBA
{
private:
    int _r;
    int _g;
    int _b;
    int _a;

public:
    RGBA(int r, int g, int b, int a);

    array<int, 4> Unpack() const;

    RGBA operator*(double const &other) const;
};
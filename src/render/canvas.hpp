#include <vector>
#include "rgba.hpp"

using namespace std;

class Canvas
{
private:
    int _height;
    int _width;
    vector<RGBA> _pixels;

public:
    Canvas(int height, int width);

    vector<int> Render() const;
};
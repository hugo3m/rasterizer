#pragma once

#include <vector>
#include "vec.hpp"

using namespace std;

vector<Vec2> InterpolateVec2(Vec2 from, Vec2 to);

vector<double> Interpolate(double intervalBegin, double valueBegin, double intervalEnd, double valueEnd);
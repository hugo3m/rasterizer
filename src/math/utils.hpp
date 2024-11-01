#pragma once

#include <vector>
#include "vec.hpp"

using namespace std;

vector<Vec2> InterpolateVec2(Vec2 from, Vec2 to);

vector<int> InterpolateX(Vec2 from, Vec2 to);

vector<int> InterpolateY(Vec2 from, Vec2 to);
#include <stdio.h>
#include <array>
#include <string>
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>

#include "render/canvas.hpp"

using namespace std;

int main()
{
    printf("Hello World\n");
    return 0;
}

vector<int> draw()
{
    Canvas canvas(200, 200);
    vector<int> res(200 * 200 * 4, 255);
    canvas.Render(res);
    printf("Hello %d %d %d %d\n", res[0], res[1], res[2], res[2]);
    return res;
}

EMSCRIPTEN_BINDINGS(module)
{
    // register functions
    emscripten::function("draw", &draw);
    // register bindings for std::vector<int>, std::map<int, std::string>, and
    // std::optional<std::string>.
    emscripten::register_vector<int>("vector<int>");
}

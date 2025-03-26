#include <stdio.h>
#include <array>
#include <string>
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>

#include "render/rasterizer.hpp"
#include "enums.hpp"

using namespace std;

#include <sys/stat.h>

bool fileExists(const char *path)
{
    struct stat buffer;
    return stat(path, &buffer) == 0;
}

int main()
{
    if (fileExists("assets/crate-texture.jpg"))
    {
        printf("File exists!!!\n");
    }
    else
    {
        printf("❌ File NOT found!\n");
    }
}

EMSCRIPTEN_BINDINGS(module)
{
    emscripten::class_<Rasterizer>("Rasterizer")
        .constructor<>()
        .function("Input", &Rasterizer::Input)
        .function("Render", &Rasterizer::Render)
        .function("Draw", &Rasterizer::Draw);
    emscripten::enum_<DrawingMethod>("DrawingMethod")
        .value("WIREFRAMED", DrawingMethod::WIREFRAMED)
        .value("FILLED", DrawingMethod::FILLED);
    // register bindings for std::vector<int>, std::map<int, std::string>, and
    // std::optional<std::string>.
    emscripten::register_vector<int>("vector<int>");
}

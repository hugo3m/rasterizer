#include <stdio.h>
#include <array>
#include <string>
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>

#include "render/rasterizer.hpp"
#include "enums.hpp"

using namespace std;

int main()
{
    return 0;
}

void freeBuffer(uintptr_t ptr)
{
    delete[] reinterpret_cast<uint8_t *>(ptr);
}

EMSCRIPTEN_BINDINGS(module)
{
    emscripten::class_<Rasterizer>("Rasterizer")
        .constructor<int, int, ShadingMethod>()
        .function("Input", &Rasterizer::Input)
        .function("Render", &Rasterizer::Render)
        .function("Draw", &Rasterizer::Draw)
        .function("DrawNative", &Rasterizer::DrawNative);
    emscripten::enum_<ShadingMethod>("ShadingMethod")
        .value("WIREFRAMED", ShadingMethod::WIREFRAMED)
        .value("FLAT_SHADING", ShadingMethod::FLAT_SHADING)
        .value("GOUREAU_SHADING", ShadingMethod::GOUREAU_SHADING)
        .value("PONG_SHADING", ShadingMethod::PONG_SHADING);
    emscripten::function("freeBuffer", &freeBuffer);
    // register bindings for std::vector<int>, std::map<int, std::string>, and
    // std::optional<std::string>.
    emscripten::register_vector<int>("vector<int>");
}

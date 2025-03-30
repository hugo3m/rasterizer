#include <stdio.h>
#include <array>
#include <string>
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>

#include "render/rasterizer.hpp"
#include "enums.hpp"

using namespace std;

// #define STB_IMAGE_IMPLEMENTATION
// #include "includes/stb_image.h"

// #include <sys/stat.h>

// bool fileExists(const char *path)
// {
//     struct stat buffer;
//     return stat(path, &buffer) == 0;
// }

int main()
{
    // const char *path = "assets/crate-texture.jpg";

    // if (!fileExists(path))
    // {
    //     printf("❌ File not found: \n");
    //     return 1;
    // }

    // int width, height, channels;
    // unsigned char *data = stbi_load(path, &width, &height, &channels, 0);

    // if (!data)
    // {
    //     printf("❌ Failed to load image: \n");
    //     return 1;
    // }

    // printf("Image loaded!! \n");

    // stbi_image_free(data);
    return 0;
}

EMSCRIPTEN_BINDINGS(module)
{
    emscripten::class_<Rasterizer>("Rasterizer")
        .constructor<int, int, ShadingMethod>()
        .function("Input", &Rasterizer::Input)
        .function("Render", &Rasterizer::Render)
        .function("Draw", &Rasterizer::Draw);
    emscripten::enum_<ShadingMethod>("ShadingMethod")
        .value("WIREFRAMED", ShadingMethod::WIREFRAMED)
        .value("FLAT_SHADING", ShadingMethod::FLAT_SHADING)
        .value("GOUREAU_SHADING", ShadingMethod::GOUREAU_SHADING)
        .value("PONG_SHADING", ShadingMethod::PONG_SHADING);
    // register bindings for std::vector<int>, std::map<int, std::string>, and
    // std::optional<std::string>.
    emscripten::register_vector<int>("vector<int>");
}

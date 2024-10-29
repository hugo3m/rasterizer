#include <stdio.h>
#include <vector>
#include <string>
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>

int main()
{
    printf("Hello World\n");
    return 0;
}

void myFunction()
{
    printf("RUN MY FUNCTION YEAAAAH\n");
}

std::vector<int> returnVectorData()
{
    std::vector<int> v = {1, 2, 3, 4, 12};
    printf("returnVectorData\n");
    return v;
}

EMSCRIPTEN_BINDINGS(module)
{
    // register functions
    emscripten::function("returnVectorData", &returnVectorData);
    emscripten::function("myFunction", &myFunction);
    // register bindings for std::vector<int>, std::map<int, std::string>, and
    // std::optional<std::string>.
    emscripten::register_vector<int>("vector<int>");
}

cmake_minimum_required(VERSION 3.14)
project("nextjscpplate" CXX)

#########################
####   TESTING       ####
#########################
# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#########################
####   EMSCRIPTEN    ####
#########################
set(EMSCRIPTEN_ROOT $ENV{EMSDK}/upstream/emscripten)
set(CMAKE_TOOLCHAIN_FILE ${EMSCRIPTEN_ROOT}/cmake/Modules/Platform/Emscripten.cmake)
set(EMCC_ARGS
  -sMODULARIZE
  -sENVIRONMENT='web'
  -sSINGLE_FILE=1
  -sALLOW_MEMORY_GROWTH=1
  # -sMAXIMUM_MEMORY=4GB
  -s -lembind
)

# define subdirectory
add_subdirectory(src)
add_subdirectory(tests)

#########################
####  BUILD TEST     ####
#########################
enable_testing()
add_executable(
  try_test
  ${TEST_FILES}
  ${SRC_FILES}
)
target_link_libraries(
  try_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(try_test)

#########################
####  BUILD WASM     ####
#########################
add_custom_command(
    OUTPUT cpp
    COMMAND em++ ${SRC_FILES} ${MAIN_FILE} --emit-tsd cpp.d.ts -o cpp.js ${EMCC_ARGS}
    COMMENT "building src"
    VERBATIM)
add_custom_target(run ALL DEPENDS cpp)
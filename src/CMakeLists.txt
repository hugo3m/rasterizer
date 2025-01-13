SET(SRC_FILES
    # instances
    ${CMAKE_CURRENT_SOURCE_DIR}/instances/camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/instances/instance.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/instances/rotation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/instances/transform.cpp
    # math
    ${CMAKE_CURRENT_SOURCE_DIR}/math/matrix.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math/plane.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math/sphere.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math/triangle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math/utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math/vec.cpp
    # meshes
    ${CMAKE_CURRENT_SOURCE_DIR}/meshes/cube.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/meshes/custom.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/meshes/mesh.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/meshes/triangle.cpp
    # render
    ${CMAKE_CURRENT_SOURCE_DIR}/render/rgba.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/canvas.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/rasterizer.cpp
    CACHE STRING "src_files"
)

SET(MAIN_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    CACHE STRING "main_file"
)
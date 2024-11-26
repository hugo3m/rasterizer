SET(SRC_FILES
    # instance
    ${CMAKE_CURRENT_SOURCE_DIR}/instance.cpp
    # math
    ${CMAKE_CURRENT_SOURCE_DIR}/math/triangle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math/utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math/vec.cpp
    # models
    ${CMAKE_CURRENT_SOURCE_DIR}/models/cube.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/models/triangle.cpp
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
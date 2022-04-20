cmake_minimum_required(VERSION 3.0.0)
project(cub3d VERSION 0.1.0)

include(CTest)
enable_testing()

find_library(APPKIT AppKit)
if (NOT APPKIT)
    message(FATAL_ERROR "AppKit not found")
endif()

find_library(OPENGL OpenGL)
if (NOT OPENGL)
    message(FATAL_ERROR "OPENGL not found")
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/includes
    ${CMAKE_CURRENT_SOURCE_DIR}/mlx
)

add_executable(cub2d
    cub2d.c
    core.c
    render.c
    cubparse.c
    util.c
    line.c
)

add_executable(cub3d
    cub3d.c
    core.c
    render.c
    cubparse.c
    util.c
    line.c
)

target_link_libraries(cub2d
    ${CMAKE_CURRENT_SOURCE_DIR}/mlx/libmlx.a
    ${APPKIT}
    ${OPENGL}
)

add_custom_command(TARGET cub2d PRE_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/mlx
    COMMAND make
    COMMENT "Building mlx..."
)

target_link_libraries(cub3d
    ${CMAKE_CURRENT_SOURCE_DIR}/mlx/libmlx.a
    ${APPKIT}
    ${OPENGL}
)

add_custom_command(TARGET cub3d PRE_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/mlx
    COMMAND make
    COMMENT "Building mlx..."
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

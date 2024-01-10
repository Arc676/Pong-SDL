cmake_minimum_required(VERSION 3.28)

project(
    "Pong SDL"
    VERSION 1.0.0
    HOMEPAGE_URL "https://github.com/Arc676/Pong-SDL"
    LANGUAGES C;CXX
    )

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(dependencies)

find_package(SDL2_image REQUIRED)

set(SRCS
    ball.c
    player.c
    state.c
    score.c
    util.c
    ui.cpp
    main.c
    )
add_executable(pong ${SRCS})
target_include_directories(pong PUBLIC
    ${imgui_SRC}
    ${imgui_SRC}/backends)
target_link_libraries(pong PUBLIC imgui SDL2 SDL2_image)

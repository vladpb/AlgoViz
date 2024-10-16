cmake_minimum_required(VERSION 3.28)
project(AlgoViz C)

set(CMAKE_C_STANDARD 11)

set(SDL2_PATH "C:/Users/vladb/CLionProjects/AlgoViz/libs/SDL2")
set(SDL2_TTF_PATH "C:/Users/vladb/CLionProjects/AlgoViz/libs/SDL2_ttf")

include_directories(${SDL2_PATH}/include)
include_directories(${SDL2_TTF_PATH}/include)

link_directories(${SDL2_PATH}/lib/x64)
link_directories(${SDL2_TTF_PATH}/lib/x64)

add_executable(AlgoViz src/main.c
        src/app.c
        src/menu.c
        src/particles.c
        src/visualization.c
        src/sorting.c
)

target_link_libraries(AlgoViz SDL2main SDL2 SDL2_ttf)

add_custom_command(TARGET AlgoViz POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_PATH}/lib/x64/SDL2.dll"
        "${SDL2_TTF_PATH}/lib/x64/SDL2_ttf.dll"
        $<TARGET_FILE_DIR:AlgoViz>
)

add_custom_command(TARGET AlgoViz POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:AlgoViz>/assets
)

set_target_properties(AlgoViz PROPERTIES WIN32_EXECUTABLE TRUE)
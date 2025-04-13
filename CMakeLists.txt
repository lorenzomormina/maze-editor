cmake_minimum_required(VERSION 3.27)
project(main)

file(GLOB CPP_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB HPP_FILES ${PROJECT_SOURCE_DIR}/src/*.h)
add_executable(main ${CPP_FILES} ${HPP_FILES} "src/Application.cpp" "src/Application.h" "src/constants.h" "src/EventHandler.cpp" "src/EventHandler.h" "src/Grid.cpp" "src/Grid.h" "src/IconButton.cpp" "src/IconButton.h" "src/main.cpp" "src/Maze.cpp" "src/Maze.h" "src/MObject.cpp" "src/MObject.h" "src/Rect.cpp" "src/Rect.h" "src/Renderer.cpp" "src/Renderer.h" "src/Screen.cpp" "src/Screen.h" "src/SDLManager.cpp" "src/SDLManager.h" "src/TextButton.cpp" "src/TextButton.h" "src/Texture.cpp" "src/Texture.h" "src/Toolbar.cpp" "src/Toolbar.h" "src/Vector2.cpp" "src/Vector2.h" "src/Window.cpp" "src/Window.h"   "src/Font.h" "src/ConfirmationPrompt.h" "src/playing/PToolbar.h" "src/playing/PToolbar.cpp" "src/playing/PlayingMaze.h")

target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/src)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(main
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

find_package(SDL2_image CONFIG REQUIRED)
target_link_libraries(main PRIVATE $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)

find_package(SDL2_ttf CONFIG REQUIRED)
target_link_libraries(main PRIVATE $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resource DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
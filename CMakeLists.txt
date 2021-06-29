project(Aerohockey)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_FLAGS "-std=c++17")
set(CMAKE_CXX_COMPILER g++-9)
include_directories(game/include)

add_executable(server.out game/src/dynamic.cpp game/src/main_server.cpp game/src/server.cpp)
add_executable(client.out game/src/client.cpp game/src/dynamic.cpp game/src/game.cpp game/src/interface.cpp game/src/main_client.cpp game/src/scoreboard.cpp game/src/textbox.cpp )

target_link_libraries(server.out PRIVATE sfml-window sfml-system sfml-audio sfml-network sfml-graphics)
target_link_libraries(client.out PRIVATE sfml-window sfml-system sfml-audio sfml-network sfml-graphics)
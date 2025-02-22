cmake_minimum_required(VERSION 3.15)
project(open_cli VERSION 0.1.0 LANGUAGES C CXX)

include(FetchContent)
FetchContent_Declare(
    cli11_proj
    QUIET
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.3.2
)
FetchContent_MakeAvailable(cli11_proj)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(open_cli src/main.cpp)

target_link_libraries(open_cli PRIVATE CLI11::CLI11)
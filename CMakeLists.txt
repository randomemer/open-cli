cmake_minimum_required(VERSION 3.15)
project(open_cli VERSION 0.1.0 LANGUAGES C CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

# Install CLI11
include(FetchContent)
FetchContent_Declare(
    cli11_proj
    QUIET
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.3.2
)
FetchContent_MakeAvailable(cli11_proj)


file(GLOB COMMANDS "src/commands/*.cpp")
add_executable(open_cli
    src/main.cpp
    src/cli.cpp
    ${COMMANDS}
)

target_include_directories(open_cli PRIVATE 
    include
    include/commands
)

target_link_libraries(open_cli PRIVATE CLI11::CLI11)
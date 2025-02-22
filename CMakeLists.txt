cmake_minimum_required(VERSION 3.15)
project(open_cli VERSION 0.1.0 LANGUAGES C CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

# Install dependencies
include(FetchContent)

FetchContent_Declare(
    cli11_proj
    QUIET
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.3.2
)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)

FetchContent_MakeAvailable(cli11_proj)
FetchContent_MakeAvailable(json)

file(GLOB COMMANDS "src/commands/*.cpp")
add_executable(open_cli
    src/main.cpp
    src/cli.cpp
    src/util.cpp
    ${COMMANDS}
)

target_include_directories(open_cli PRIVATE 
    include
    include/commands
)

target_link_libraries(open_cli PRIVATE CLI11::CLI11)
target_link_libraries(open_cli PRIVATE nlohmann_json::nlohmann_json)
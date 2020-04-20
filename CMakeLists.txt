cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(ctad VERSION 0.0.1 LANGUAGES CXX)

# C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Target location
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Additional compile flags
set(GCC_COMPILE_FLAGS "-Wall -Wextra -Werror -Wsuggest-override -Wno-register -Wno-missing-braces -Wno-unknown-pragmas -fdiagnostics-show-option")
if(NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")
endif()

# All required dependencies
find_package(fmt CONFIG REQUIRED)

# Executable
add_executable(ctad
                    src/main.cpp
)
target_include_directories(ctad PRIVATE src/include)
target_link_libraries(ctad
    PRIVATE
        fmt::fmt
        fmt::fmt-header-only
)
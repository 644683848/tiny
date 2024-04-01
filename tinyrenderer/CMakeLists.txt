cmake_minimum_required(VERSION 3.0)
project(TGAImageExample)

#find_package(Eigen3 REQUIRED)
#include_directories(EIGEN3_INCLUDE_DIR)

# Add the executable
add_executable(TGAImageExample main.cpp
        tgaimage.cpp
        model.cpp
        geometry.cpp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# If you need to include directories
# target_include_directories(TGAImageExample PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# If you need to link libraries
# target_link_libraries(TGAImageExample PUBLIC library_name)

# If you need compiler options
# target_compile_options(TGAImageExample PRIVATE -Wall -Wextra -pedantic)

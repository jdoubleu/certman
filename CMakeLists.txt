cmake_minimum_required(VERSION 3.10)
project(certman)

# Settings
set(CMAKE_CXX_STANDARD 17)

## Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/resources)
## Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Required cmake modules
include(ExternalProject)

# Find external required pacakges
find_package(Qt5Widgets)
find_package(OpenSSL REQUIRED)

# Create executable
file(GLOB_RECURSE CERTMAN_SRC
        "src/*.h"
        "src/*.cpp"
        )
add_executable(certman ${CERTMAN_SRC})

# Link dependent libraries
target_link_libraries(certman Qt5::Widgets)
target_link_libraries(certman OpenSSL::Crypto)
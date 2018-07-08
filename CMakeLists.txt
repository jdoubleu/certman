cmake_minimum_required(VERSION 3.10)
project(certman)

# Settings
set(CMAKE_CXX_STANDARD 17)

# CMAKE settings
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

## Certman Paths
set(CERTMAN_RESOURCES_UI ${CMAKE_SOURCE_DIR}/resources/ui)
## Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CERTMAN_RESOURCES_UI}/window ${CERTMAN_RESOURCES_UI}/widget ${CERTMAN_RESOURCES_UI}/page)
## Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Required cmake modules
include(ExternalProject)

# Required custom modules
include(QtApplicationMeta)

# project meta information
set(COMPANY "Certman")
set(COPYRIGHT "Copyright (c) 2018 Max van Aerssen, Timo Ribbers, Joshua Westerheide. All rights reserved.")
set(IDENTIFIER "de.hs-duesseldorf.certman")

add_project_meta(META_FILES_TO_INCLUDE)

# Find external required pacakges
find_package(Qt5Widgets)
find_package(OpenSSL REQUIRED)

# Create executable
file(GLOB_RECURSE CERTMAN_SRC "src/*.h" "src/*.cpp")

add_executable(${PROJECT_NAME} ${OS_BUNDLE} ${CERTMAN_SRC} ${META_FILES_TO_INCLUDE})

# Link dependent libraries
target_link_libraries(certman Qt5::Widgets)
target_link_libraries(certman OpenSSL::Crypto)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Now simply link against gtest or gtest_main as needed. Eg
file(GLOB_RECURSE CERTMAN_UNIT_TESTS "tests/unit/*.cpp")
file(GLOB_RECURSE CERTMAN_TEST_SRC "src/*/*.h" "src/*/*.cpp")
set(CERTMAN_TEST_FIXTURES ${PROJECT_SOURCE_DIR}/tests/fixtures)
add_definitions(-DCERTMAN_TEST_FIXTURES=${CERTMAN_TEST_FIXTURES})
add_executable(unit ${CERTMAN_UNIT_TESTS} ${CERTMAN_TEST_SRC})
target_link_libraries(unit gtest_main)
target_link_libraries(unit Qt5::Widgets)
target_link_libraries(unit OpenSSL::Crypto)
add_test(NAME unit_test COMMAND unit)

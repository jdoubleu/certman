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

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()

    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${doxyfile_in} ${doxyfile} @ONLY)

    add_custom_target(doc
            COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)

endif()
